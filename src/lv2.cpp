#include "./uris.h"
#include "./musictypes.h"

#include "lv2/atom/atom.h"
#include "lv2/atom/util.h"
#include "lv2/core/lv2.h"
#include "lv2/core/lv2_util.h"
#include "lv2/log/log.h"
#include "lv2/log/logger.h"
#include "lv2/midi/midi.h"
#include "lv2/urid/urid.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

enum
{
    CHORDIFY_INPUT = 0,
    CHORDIFY_OUTPUT = 1
};

typedef struct
{
    // Music structures
    Scale *scale;

    // Features
    LV2_URID_Map *map;
    LV2_Log_Logger logger;

    // Ports
    const LV2_Atom_Sequence *in_port;
    LV2_Atom_Sequence *out_port;

    // URIs
    ChordifyURIs uris;
} Chordify;

static void
connect_port(LV2_Handle instance, uint32_t port, void *data)
{
    Chordify *self = (Chordify *)instance;
    switch (port)
    {
    case CHORDIFY_INPUT:
        self->in_port = (const LV2_Atom_Sequence *)data;
        break;
    case CHORDIFY_OUTPUT:
        self->out_port = (LV2_Atom_Sequence *)data;
        break;
    default:
        break;
    }
}

static LV2_Handle
instantiate(const LV2_Descriptor *descriptor,
            double rate,
            const char *path,
            const LV2_Feature *const *features)
{
    // Allocate and initialise instance structure.
    Chordify *self = (Chordify *)calloc(1, sizeof(Chordify));
    if (!self)
    {
        return NULL;
    }

    // Scan host features for URID map
    // clang-format off
  const char*  missing = lv2_features_query(
    features,
    LV2_LOG__log,  &self->logger.log, false,
    LV2_URID__map, &self->map,        true,
    NULL);
    // clang-format on

    lv2_log_logger_set_map(&self->logger, self->map);
    if (missing)
    {
        lv2_log_error(&self->logger, "Missing feature <%s>\n", missing);
        free(self);
        return NULL;
    }

    map_chordify_uris(self->map, &self->uris);

    self->scale = new Scale(Sound::C, MusicVariant::MAJOR);

    return (LV2_Handle)self;
}

static void
cleanup(LV2_Handle instance)
{
    free(instance);
}

static void
run(LV2_Handle instance, uint32_t sample_count)
{
    Chordify *self = (Chordify *)instance;
    ChordifyURIs *uris = &self->uris;

    typedef struct
    {
        LV2_Atom_Event event;
        uint8_t msg[3];
    } MIDINoteEvent;

    // Initially self->out_port contains a Chunk with size set to capacity

    // Get the capacity
    const uint32_t out_capacity = self->out_port->atom.size;

    // Write an empty Sequence header to the output
    lv2_atom_sequence_clear(self->out_port);
    self->out_port->atom.type = self->in_port->atom.type;

    LV2_ATOM_SEQUENCE_FOREACH(self->in_port, ev)
    {
        if (ev->body.type == uris->midi_Event)
        {
            const uint8_t *const msg = (const uint8_t *)(ev + 1);
            switch (lv2_midi_message_type(msg))
            {
            case LV2_MIDI_MSG_NOTE_ON:
            case LV2_MIDI_MSG_NOTE_OFF:
                lv2_atom_sequence_append_event(self->out_port, out_capacity, ev);

                if (msg[1] <= 127 - 7)
                {

                    for (
                        auto &x :
                        self->scale->get_chord_by_note(
                            static_cast<Sound>(msg[1] % 12),
                            msg[1] / 12))
                    {
                        MIDINoteEvent interval;

                        interval.event.time.frames = ev->time.frames; // Same time
                        interval.event.body.type = ev->body.type;     // Same type
                        interval.event.body.size = ev->body.size;     // Same size

                        interval.msg[0] = msg[0]; // Same status
                        interval.msg[1] = x;      // Pitch up 7 semitones
                        interval.msg[2] = msg[2]; // Same velocity

                        lv2_atom_sequence_append_event(
                            self->out_port, out_capacity, &interval.event);
                    }
                }
                break;
            default:
                lv2_atom_sequence_append_event(self->out_port, out_capacity, ev);
                break;
            }
        }
    }
}

static const void *
extension_data(const char *uri)
{
    return NULL;
}

static const LV2_Descriptor descriptor = {CHORDIFY_URI,
                                          instantiate,
                                          connect_port,
                                          NULL, // activate,
                                          run,
                                          NULL, // deactivate,
                                          cleanup,
                                          extension_data};

LV2_SYMBOL_EXPORT
const LV2_Descriptor *
lv2_descriptor(uint32_t index)
{
    return index == 0 ? &descriptor : NULL;
}