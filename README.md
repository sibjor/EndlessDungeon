# Project: Endless Dungeon

- Author: Sixten Björling
- Issued by teacher Sebastan Jensen at Forsbergs game programming school Stockholm/Sweden
- Please build to generate compile_commands.json
- Deletion of /build can be necessary between cmake configurations

```bash
# Fetch and build
mkdir sibjor
cd sibjor
git clone https://github.com/sibjor/EndlessDungeon.git
cd EndlessDungeon
cmake -S . -B build
cmake --build build
```
```bash
# Build for the web
emcmake cmake -S . -B build-web
emmake make -C build-web
```
```bash
# Build and host web-build on port 8888
cd tools
cd server
go build -o server server.go
./server
```

Generating procedural content has always been an important part of game programming: generating assets programmatically saves time and space and allows us to do more with less. However, since the days of the original Rogue, games based on the premise of procedural generation have also become a popular genre of its own because it opens up a game design space rife with possibilities for creativity.

Your task is to create the dungeon generation part of a game, which can be implemented in many different ways from very easy to very complex. Dungeons are often laid out on simple 2D grid arrays but are often connected to higher-level data structures such as graphs for generation purposes. Many of the algorithms used for dungeon generation are indeed variations on graph traversal algorithms like Breadth First Search and Depth First Search. I do not require you to implement any specific algorithm and for this project research is as important as implementation. To this end, you will find a list of starting resources at the end of this document.

## Passing (G) Projects

Passing projects have:
- [ ] Dungeons have corridors and rooms (but not necessarily doors)
- [ ] Dungeons have a starting point and an end point (stairs up/down)
- [ ] A new dungeon can be generated somehow (pressing spacebar)

## Passing with Distinction (VG) Projects

Passing with distinction projects additionally have at least 3 of the following:
- [ ] Dungeons have doors
- [ ] Dungeons have treasure
- [ ] Dungeons have monsters
- [ ] There are different room types
- [ ] Some doors are locked and require keys
- [ ] Some rooms, doors, or tiles are trapped
- [ ] You can control an avatar in the dungeon (turn-based or real-time)
- [ ] Dungeons become progressively more difficult/complex
- [ ] Polish (menus, UI, etc.)
- [ ] Other complexities…

## Resources

- [Algorithm is Not a Four-Letter Word (on maze generation)](https://www.jamisbuck.org/presentations/rubyconf2011/index.html#connected-graph)
- [Spelunky Level Generation](https://www.youtube.com/watch?v=Uqk5Zf0tw3o)
- [Mazes For Programmers (Book)](https://www.kufunda.net/publicdocs/Mazes%20for%20Programmers%20Code%20Your%20Own%20Twisty%20Little%20Passages%20(Jamis%20Buck).pdf)
- [Herbert Wolverson on Procedural Dungeon Generation](https://www.youtube.com/watch?v=TlLIOgWYVpI)
- [Caves Of Quds algorithm (Wave function collapse) - Advanced](https://www.youtube.com/watch?v=fnFj3dOKcIQ)
- [Map generation articles on RogueBasin](https://roguebasin.com/index.php/Articles#Map)