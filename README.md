# 🎼 Whst is this plugin

This plugin's goal is to produce chords in selected scale based on played note. I am creating it basically to learn how to code music plugins therefore I am planing to actually support VST build later. This project is based on [example](https://lv2plug.in/book/#_fifths) lv2 plugin on lv2's page

# 🔨 Building

On linux to build go with

```sh
cmake .
make
```

Then you should have direcotry `build/chordify.lv2`. When you paste this directory to any lv2 directory it should be dtected by host at the next start.

Since I use **CMake** you should be able to go with any IDE and compiler.

---

**TO DO:**

-   [ ] make VST build
-   [ ] add UI
-   [ ] test on windows
-   [ ] update gitignore for diffrent possible IDEs
