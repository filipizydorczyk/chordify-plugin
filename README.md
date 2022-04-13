This repository is archived now. I kind of lost motivation for this project and also wanted to do way more than I was capeable at time. I will get back to lv2 plugins with simpler projects.

---

# 🎼 Whst is this plugin

This plugin's goal is to produce chords in selected scale based on played note. I am creating it basically to learn how to code music plugins therefore I am planing to actually support VST build later. This project is based on [example](https://lv2plug.in/book/#_fifths) lv2 plugin on lv2's page

# 🔨 Building

On linux to build go with

```sh
cmake .
make
```

Then you should have direcotry `build/chordify.lv2`. On linux there is post build command that also automaticly copy this directory to `~/.lv2` so that you can instantly test it at any host. You can also run script `./scripts/install-build.sh`.

There is no windows scripts at the moment.
