**WORK IN PROGRESS**

# Tortimer

**Tortimer** is a homebrew program for the Nintendo 64 that allows for transferring NES games from the SD Card to a Controller Pak for use in *Doubutsu no Mori* (Animal Forest).

In *Doubutsu no Mori*, players can obtain a special in-game *Disk System* furniture item. When interacted with, this item scans the inserted Controller Pak for specially formatted NES ROM files. If a valid file is detected, the game launches it using its built-in NES emulator, *ksNes*.

This project has two functions: it can send the *Disk System* item to the Controller Pak to be retrieved at the post office in-game, as well as generate Controller Pak notes containing NES ROMs using Nintendo's custom NESINFO header and Yay0 compression.

# Usage

1. Be sure you have progressed into *Doubutsu no Mori* to the point where your character's part time job is finished.
2. Open Tortimer and select the option to send the Disk System letter data to your Controller Pak.
3. Return to *Doubutsu no Mori* and visit the post office. Choose the third option to open letter data from the Controller Pak. The letter within should contain the Disk System item which can be placed in your house.
4. Open Tortimer and select an NES ROM to send to the Controller Pak.
5. Return to *Doubutsu no Mori* and interact with the Disk System item in your house. The game should find the NES ROM on your Controller Pak and ask if you would like to play it.

From this point on, steps 4 and 5 can be repeated indefinitely so long as you keep the Disk System item.

# Supported games

Virtually any NES ROM can be sent to the Controller Pak so long as there is space for it, though official Controller Paks only support ROMs that fit within 123 "pages." Tortimer supports Nintendo's Yay0 compression algorithm, which expands the number of possible supported games. Modified Controller Paks or the Ares emulator can be used play even larger NES ROMs.

This is a list of NES games that should fit on a standard Controller Pak. This list is not all-inclusive, and it does not guarantee the games will run correctly, just that they will fit:

| Filename | Raw size | Compressed size | Needs compression |
|----------|----------|-----------------|-----------|
| 10-Yard Fight (USA, Europe) | 40976 (161 pages) | 19337 (76 pages) | ✔ |
| 1942 (Japan, USA) (En) | 40976 (161 pages) | 29598 (116 pages) | ✔ |
| 4 Nin Uchi Mahjong (Japan) (Rev 1) | 24592 (97 pages) | 17645 (69 pages) | |
| Argus (Japan) | 49168 (193 pages) | 29564 (116 pages) | ✔ |
| Arkanoid (USA) | 49168 (193 pages) | 24236 (95 pages) | ✔ |
| Astro Robo Sasa (Japan) | 40976 (161 pages) | 24924 (98 pages) | ✔ |
| B-Wings (Japan) | 40976 (161 pages) | 28566 (112 pages) | ✔ |
| Balloon Fight (USA) | 24592 (97 pages) | 18171 (71 pages) | |
| Baltron (Japan) | 40976 (161 pages) | 26803 (105 pages) | ✔ |
| Banana (Japan) | 49168 (193 pages) | 30148 (118 pages) | ✔ |
| Baseball (USA, Europe) | 24592 (97 pages) | 19381 (76 pages) | |
| BattleCity (Japan) | 24592 (97 pages) | 17488 (69 pages) | |
| Binary Land (Japan) | 24592 (97 pages) | 12737 (50 pages) | |
| Bird Week (Japan) | 24592 (97 pages) | 18380 (72 pages) | |
| Bokosuka Wars (Japan) | 40976 (161 pages) | 21017 (83 pages) | ✔ |
| Bomberman (USA) | 24592 (97 pages) | 18285 (72 pages) | |
| BurgerTime (USA) | 24592 (97 pages) | 16715 (66 pages) | |
| Chack'n Pop (Japan) | 24592 (97 pages) | 16784 (66 pages) | |
| Challenger (Japan) | 40976 (161 pages) | 30181 (118 pages) | ✔ |
| Championship Lode Runner (Japan) | 24592 (97 pages) | 19393 (76 pages) | |
| Chou Fuyuu Yousai - Exed Exes (Japan) | 40976 (161 pages) | 27275 (107 pages) | ✔ |
| Choujikuu Yousai - Macross (Japan) | 24592 (97 pages) | 18407 (72 pages) | |
| Chubby Cherub (USA) | 40976 (161 pages) | 27172 (107 pages) | ✔ |
| Circus Charlie (Japan) | 24592 (97 pages) | 19811 (78 pages) | |
| Clu Clu Land (World) | 24592 (97 pages) | 18588 (73 pages) | |
| Defender II (USA) | 24592 (97 pages) | 14883 (59 pages) | |
| Devil World (Europe) | 24592 (97 pages) | 18908 (74 pages) | |
| Dig Dug (Japan) | 24592 (97 pages) | 16985 (67 pages) | |
| Dig Dug II - Trouble in Paradise (USA) | 40976 (161 pages) | 29249 (115 pages) | ✔ |
| Donkey Kong (World) (Rev 1) | 24592 (97 pages) | 18458 (73 pages) | |
| Donkey Kong 3 (World) | 24592 (97 pages) | 19054 (75 pages) | |
| Donkey Kong Jr. (World) (Rev 1) | 24592 (97 pages) | 19224 (76 pages) | |
| Donkey Kong Jr. + Jr. Lesson (Japan) | 24592 (97 pages) | 19438 (76 pages) | |
| Donkey Kong Jr. Math (USA, Europe) | 24592 (97 pages) | 19392 (76 pages) | |
| Door Door (Japan) | 24592 (97 pages) | 16163 (64 pages) | |
| Dough Boy (Japan) | 40976 (161 pages) | 27430 (108 pages) | ✔ |
| Druaga no Tou (Japan) | 40976 (161 pages) | 27561 (108 pages) | ✔ |
| Duck Hunt (World) | 24592 (97 pages) | 18248 (72 pages) | |
| Elevator Action (USA) | 40976 (161 pages) | 25341 (99 pages) | ✔ |
| Excitebike (Japan, USA) (En) | 24592 (97 pages) | 20062 (79 pages) | |
| Exerion (Japan) (En) | 24592 (97 pages) | 15806 (62 pages) | |
| F1 Race (Japan) | 24592 (97 pages) | 17448 (69 pages) | |
| Field Combat (Japan) | 24592 (97 pages) | 17132 (67 pages) | |
| Fisher-Price - I Can Remember (USA) | 65552 (257 pages) | 31236 (123 pages) | ✔ |
| Fisher-Price - Perfect Fit (USA) | 65552 (257 pages) | 28380 (111 pages) | ✔ |
| Flappy (Japan) | 40976 (161 pages) | 27670 (109 pages) | ✔ |
| Formation Z (Japan) (Rev 1) | 24592 (97 pages) | 16489 (65 pages) | |
| Front Line (Japan) | 24592 (97 pages) | 15161 (60 pages) | |
| Galaga - Demons of Death (USA) | 40976 (161 pages) | 19207 (76 pages) | ✔ |
| Galaxian (Japan) (Rev 1) | 16400 (65 pages) | 11463 (45 pages) | |
| Geimos (Japan) | 40976 (161 pages) | 22719 (89 pages) | ✔ |
| Golf (USA, Asia) (En) | 24592 (97 pages) | 18740 (74 pages) | |
| Gomoku Narabe (Japan) | 24592 (97 pages) | 14757 (58 pages) | |
| Gyrodine (Japan) | 40976 (161 pages) | 24626 (97 pages) | ✔ |
| Gyromite (World) | 40976 (161 pages) | 26762 (105 pages) | ✔ |
| Hogan's Alley (World) | 24592 (97 pages) | 17505 (69 pages) | |
| Honshougi - Naitou 9 Dan Shougi Hiden (Japan) | 24592 (97 pages) | 17145 (67 pages) | |
| Hydlide (USA) | 40976 (161 pages) | 25942 (102 pages) | ✔ |
| Hyper Sports (Japan) (Rev 1) | 24592 (97 pages) | 20201 (79 pages) | |
| Ice Climber (USA, Europe, Korea) (En) | 24592 (97 pages) | 20710 (81 pages) | |
| Igo - Kyuu Roban Taikyoku (Japan) | 49168 (193 pages) | 29474 (116 pages) | ✔ |
| Igo Meikan (Japan) | 40976 (161 pages) | 28922 (113 pages) | ✔ |
| Ikinari Musician (Japan) | 49168 (193 pages) | 26965 (106 pages) | ✔ |
| Ikki (Japan) | 24592 (97 pages) | 19057 (75 pages) | |
| Joust (USA) | 32784 (129 pages) | 21809 (86 pages) | ✔ |
| Karateka (Japan) | 24592 (97 pages) | 16671 (66 pages) | |
| Kekkyoku Nankyoku Daibouken (Japan) (Rev 1) | 24592 (97 pages) | 18143 (71 pages) | |
| Kidou Senshi Z Gundam - Hot Scramble (Japan) (Final Version) | 40976 (161 pages) | 28575 (112 pages) | ✔ |
| Lode Runner (USA) | 24592 (97 pages) | 18782 (74 pages) | |
| Lot Lot (Japan) | 40976 (161 pages) | 22436 (88 pages) | ✔ |
| Lunar Pool (USA) | 24592 (97 pages) | 18647 (73 pages) | |
| M.U.S.C.L.E. - Tag Team Match (USA) | 24592 (97 pages) | 17481 (69 pages) | |
| Mach Rider (Japan, USA) (En) (Rev 1) | 40976 (161 pages) | 29683 (116 pages) | ✔ |
| Magmax (USA) | 40976 (161 pages) | 29090 (114 pages) | ✔ |
| Mahjong (Japan) (Rev 2) | 24592 (97 pages) | 18522 (73 pages) | |
| Mappy (Japan) | 24592 (97 pages) | 17630 (69 pages) | |
| Mario Bros. (World) | 24592 (97 pages) | 18979 (75 pages) | |
| Millipede (USA) | 24592 (97 pages) | 17561 (69 pages) | |
| Ms. Pac-Man (USA) (Namco) | 40976 (161 pages) | 20121 (79 pages) | ✔ |
| Ninja Hattori-kun - Ninja wa Syugyou de Gozaru no Maki (Japan) | 40976 (161 pages) | 30303 (119 pages) | ✔ |
| Ninja Jajamaru-kun (Japan) | 32784 (129 pages) | 23309 (92 pages) | ✔ |
| Ninja-kun - Majou no Bouken (Japan) (Rev 1) | 24592 (97 pages) | 16295 (64 pages) | |
| Nuts & Milk (Japan) | 24592 (97 pages) | 16118 (63 pages) | |
| Onyanko Town (Japan) | 40976 (161 pages) | 25642 (101 pages) | ✔ |
| Othello (USA) | 40976 (161 pages) | 20131 (79 pages) | ✔ |
| Pac-Land (Japan) | 40976 (161 pages) | 26544 (104 pages) | ✔ |
| Pac-Man (USA) (Namco) | 24592 (97 pages) | 13114 (52 pages) | |
| Pachicom (Japan) | 40976 (161 pages) | 27651 (109 pages) | ✔ |
| Peepar Time (Japan) | 49168 (193 pages) | 31158 (122 pages) | ✔ |
| Penguin-kun Wars (Japan) | 40976 (161 pages) | 25359 (100 pages) | ✔ |
| Pinball (Japan, USA) (En) | 24592 (97 pages) | 18133 (71 pages) | |
| Pooyan (Japan) | 24592 (97 pages) | 17640 (69 pages) | |
| Popeye (World) (Rev 1) | 24592 (97 pages) | 18894 (74 pages) | |
| Popeye no Eigo Asobi (Japan) | 24592 (97 pages) | 19186 (75 pages) | |
| Portopia Renzoku Satsujin Jiken (Japan) | 40976 (161 pages) | 30468 (120 pages) | ✔ |
| Raid on Bungeling Bay (USA) | 24592 (97 pages) | 18712 (74 pages) | |
| Road Fighter (Europe) | 24592 (97 pages) | 18785 (74 pages) | |
| Route-16 Turbo (Japan) | 40976 (161 pages) | 25005 (98 pages) | ✔ |
| Sansuu 1 Nen - Keisan Game (Japan) | 40976 (161 pages) | 18270 (72 pages) | ✔ |
| Sansuu 2 Nen - Keisan Game (Japan) | 40976 (161 pages) | 28230 (111 pages) | ✔ |
| Sansuu 3 Nen - Keisan Game (Japan) | 40976 (161 pages) | 20678 (81 pages) | ✔ |
| Seicross (USA) | 40976 (161 pages) | 26467 (104 pages) | ✔ |
| Sky Destroyer (Japan) | 24592 (97 pages) | 18383 (72 pages) | |
| Slalom (USA) | 40976 (161 pages) | 27724 (109 pages) | ✔ |
| Soccer (Japan, USA) (En) | 40976 (161 pages) | 31194 (122 pages) | ✔ |
| Son Son (Japan) (En) | 40976 (161 pages) | 25262 (99 pages) | ✔ |
| Space Invaders (Japan) | 24592 (97 pages) | 10060 (40 pages) | |
| Spelunker (USA) | 40976 (161 pages) | 24932 (98 pages) | ✔ |
| Spy vs Spy (USA) | 40976 (161 pages) | 29459 (116 pages) | ✔ |
| Sqoon (USA) | 40976 (161 pages) | 28541 (112 pages) | ✔ |
| Stack-Up (World) | 40976 (161 pages) | 26781 (105 pages) | ✔ |
| Star Force (USA) | 65552 (257 pages) | 30151 (118 pages) | ✔ |
| Star Luster (Japan) | 40976 (161 pages) | 27301 (107 pages) | ✔ |
| Super Arabian (Japan) | 24592 (97 pages) | 17377 (68 pages) | |
| Tag Team Wrestling (USA) | 40976 (161 pages) | 31445 (123 pages) | ✔ |
| Tennis (Japan, USA) (En) | 24592 (97 pages) | 19040 (75 pages) | |
| Tetris (Bulletproof) (Japan) (Rev 2) | 49168 (193 pages) | 28076 (110 pages) | ✔ |
| Tetris (USA) | 49168 (193 pages) | 28623 (112 pages) | ✔ |
| Thexder (Japan) | 40976 (161 pages) | 19744 (78 pages) | ✔ |
| Urban Champion (World) | 24592 (97 pages) | 17440 (69 pages) | |
| Videomation (USA) | 32784 (129 pages) | 20254 (80 pages) | ✔ |
| Volguard II (Japan) (En) | 40976 (161 pages) | 30506 (120 pages) | ✔ |
| Volleyball (USA, Europe) | 40976 (161 pages) | 23453 (92 pages) | ✔ |
| Warpman (Japan) (En) (Rev 1) (Namcot Collection) | 24592 (97 pages) | 15851 (62 pages) | |
| Wild Gunman (Japan, USA) (En) | 24592 (97 pages) | 18662 (73 pages) | |
| Wrecking Crew (World) | 40976 (161 pages) | 30430 (119 pages) | ✔ |
| Xevious - The Avenger (USA) | 40976 (161 pages) | 27686 (109 pages) | ✔ |
| Yie Ar Kung-Fu (Japan) (Rev 1.4) | 24592 (97 pages) | 19141 (75 pages) | |
| Zippy Race (Japan) | 24592 (97 pages) | 17270 (68 pages) | |
