**WORK IN PROGRESS*

# Tortimer

**Tortimer** is a homebrew program for the Nintendo 64 that allows for transferring NES games from the SD Card to a Controller Pak for use in *Doubutsu no Mori* (Animal Forest).

In *Doubutsu no Mori*, players can obtain a special in-game *Famicom* furniture item. When interacted with, this item scans the inserted Controller Pak for specially formatted NES ROM files. If a valid file is detected, the game launches it using its built-in NES emulator, *ksNes*. The ROMs must conform to a specific file structure expected by *Doubutsu no Mori*, and they may optionally be stored using Nintendo’s Yay0 compression format to reduce file size. *Tortimer* can send the *Famicom* item to the Controller Pak to be retrieved at the post office in-game, as well as generate Controller Pak notes containing NES ROMs using the proper NESINFO header and Yay0 compression.

# Supported games

This is a list of NES games that should fit on a standard Controller Pak. This list is not all-inclusive, and it does not guarantee the games will run correctly, just that they will fit.

| Filename | Raw Size | Compressed Size | Supported |
|----------|----------|-----------------|-----------|
| 10-Yard Fight (USA, Europe) | 40976 bytes (161 pages) | 19337 bytes (76 pages) | compression needed |
| 1942 (Japan, USA) (En) | 40976 bytes (161 pages) | 29598 bytes (116 pages) | compression needed |
| 4 Nin Uchi Mahjong (Japan) (Rev 1) | 24592 bytes (97 pages) | 17645 bytes (69 pages) | compression not needed |
| Argus (Japan) | 49168 bytes (193 pages) | 29564 bytes (116 pages) | compression needed |
| Arkanoid (USA) | 49168 bytes (193 pages) | 24236 bytes (95 pages) | compression needed |
| Astro Robo Sasa (Japan) | 40976 bytes (161 pages) | 24924 bytes (98 pages) | compression needed |
| B-Wings (Japan) | 40976 bytes (161 pages) | 28566 bytes (112 pages) | compression needed |
| Balloon Fight (USA) | 24592 bytes (97 pages) | 18171 bytes (71 pages) | compression not needed |
| Baltron (Japan) | 40976 bytes (161 pages) | 26803 bytes (105 pages) | compression needed |
| Banana (Japan) | 49168 bytes (193 pages) | 30148 bytes (118 pages) | compression needed |
| Baseball (USA, Europe) | 24592 bytes (97 pages) | 19381 bytes (76 pages) | compression not needed |
| BattleCity (Japan) | 24592 bytes (97 pages) | 17488 bytes (69 pages) | compression not needed |
| Battleship (USA) | 65552 bytes (257 pages) | 32180 bytes (126 pages) | compression needed |
| Binary Land (Japan) | 24592 bytes (97 pages) | 12737 bytes (50 pages) | compression not needed |
| Bird Week (Japan) | 24592 bytes (97 pages) | 18380 bytes (72 pages) | compression not needed |
| Bokosuka Wars (Japan) | 40976 bytes (161 pages) | 21017 bytes (83 pages) | compression needed |
| Bomberman (USA) | 24592 bytes (97 pages) | 18285 bytes (72 pages) | compression not needed |
| BurgerTime (USA) | 24592 bytes (97 pages) | 16715 bytes (66 pages) | compression not needed |
| Chack'n Pop (Japan) | 24592 bytes (97 pages) | 16784 bytes (66 pages) | compression not needed |
| Challenger (Japan) | 40976 bytes (161 pages) | 30181 bytes (118 pages) | compression needed |
| Championship Lode Runner (Japan) | 24592 bytes (97 pages) | 19393 bytes (76 pages) | compression not needed |
| Chou Fuyuu Yousai - Exed Exes (Japan) | 40976 bytes (161 pages) | 27275 bytes (107 pages) | compression needed |
| Choujikuu Yousai - Macross (Japan) | 24592 bytes (97 pages) | 18407 bytes (72 pages) | compression not needed |
| Chubby Cherub (USA) | 40976 bytes (161 pages) | 27172 bytes (107 pages) | compression needed |
| Circus Charlie (Japan) | 24592 bytes (97 pages) | 19811 bytes (78 pages) | compression not needed |
| City Connection (USA) | 65552 bytes (257 pages) | 32617 bytes (128 pages) | compression needed |
| Clu Clu Land (World) | 24592 bytes (97 pages) | 18588 bytes (73 pages) | compression not needed |
| Defender II (USA) | 24592 bytes (97 pages) | 14883 bytes (59 pages) | compression not needed |
| Devil World (Europe) | 24592 bytes (97 pages) | 18908 bytes (74 pages) | compression not needed |
| Dig Dug (Japan) | 24592 bytes (97 pages) | 16985 bytes (67 pages) | compression not needed |
| Dig Dug II - Trouble in Paradise (USA) | 40976 bytes (161 pages) | 29249 bytes (115 pages) | compression needed |
| Donkey Kong (World) (Rev 1) | 24592 bytes (97 pages) | 18458 bytes (73 pages) | compression not needed |
| Donkey Kong 3 (World) | 24592 bytes (97 pages) | 19054 bytes (75 pages) | compression not needed |
| Donkey Kong Jr. (World) (Rev 1) | 24592 bytes (97 pages) | 19224 bytes (76 pages) | compression not needed |
| Donkey Kong Jr. + Jr. Lesson (Japan) | 24592 bytes (97 pages) | 19438 bytes (76 pages) | compression not needed |
| Donkey Kong Jr. Math (USA, Europe) | 24592 bytes (97 pages) | 19392 bytes (76 pages) | compression not needed |
| Door Door (Japan) | 24592 bytes (97 pages) | 16163 bytes (64 pages) | compression not needed |
| Dough Boy (Japan) | 40976 bytes (161 pages) | 27430 bytes (108 pages) | compression needed |
| Druaga no Tou (Japan) | 40976 bytes (161 pages) | 27561 bytes (108 pages) | compression needed |
| Duck Hunt (World) | 24592 bytes (97 pages) | 18248 bytes (72 pages) | compression not needed |
| Dynamite Bowl (Japan) (Rev 1) | 65552 bytes (257 pages) | 31595 bytes (124 pages) | compression needed |
| Elevator Action (USA) | 40976 bytes (161 pages) | 25341 bytes (99 pages) | compression needed |
| Excitebike (Japan, USA) (En) | 24592 bytes (97 pages) | 20062 bytes (79 pages) | compression not needed |
| Exerion (Japan) (En) | 24592 bytes (97 pages) | 15806 bytes (62 pages) | compression not needed |
| F1 Race (Japan) | 24592 bytes (97 pages) | 17448 bytes (69 pages) | compression not needed |
| Field Combat (Japan) | 24592 bytes (97 pages) | 17132 bytes (67 pages) | compression not needed |
| Fisher-Price - I Can Remember (USA) | 65552 bytes (257 pages) | 31236 bytes (123 pages) | compression needed |
| Fisher-Price - Perfect Fit (USA) | 65552 bytes (257 pages) | 28380 bytes (111 pages) | compression needed |
| Flappy (Japan) | 40976 bytes (161 pages) | 27670 bytes (109 pages) | compression needed |
| Formation Z (Japan) (Rev 1) | 24592 bytes (97 pages) | 16489 bytes (65 pages) | compression not needed |
| Front Line (Japan) | 24592 bytes (97 pages) | 15161 bytes (60 pages) | compression not needed |
| Galaga - Demons of Death (USA) | 40976 bytes (161 pages) | 19207 bytes (76 pages) | compression needed |
| Galaxian (Japan) (Rev 1) | 16400 bytes (65 pages) | 11463 bytes (45 pages) | compression not needed |
| Geimos (Japan) | 40976 bytes (161 pages) | 22719 bytes (89 pages) | compression needed |
| Golf (USA, Asia) (En) | 24592 bytes (97 pages) | 18740 bytes (74 pages) | compression not needed |
| Gomoku Narabe (Japan) | 24592 bytes (97 pages) | 14757 bytes (58 pages) | compression not needed |
| Gyrodine (Japan) | 40976 bytes (161 pages) | 24626 bytes (97 pages) | compression needed |
| Gyromite (World) | 40976 bytes (161 pages) | 26762 bytes (105 pages) | compression needed |
| Hogan's Alley (World) | 24592 bytes (97 pages) | 17505 bytes (69 pages) | compression not needed |
| Honshougi - Naitou 9 Dan Shougi Hiden (Japan) | 24592 bytes (97 pages) | 17145 bytes (67 pages) | compression not needed |
| Hydlide (USA) | 40976 bytes (161 pages) | 25942 bytes (102 pages) | compression needed |
| Hyper Sports (Japan) (Rev 1) | 24592 bytes (97 pages) | 20201 bytes (79 pages) | compression not needed |
| Ice Climber (USA, Europe, Korea) (En) | 24592 bytes (97 pages) | 20710 bytes (81 pages) | compression not needed |
| Ice Hockey (USA) | 40976 bytes (161 pages) | 31753 bytes (125 pages) | compression needed |
| Igo - Kyuu Roban Taikyoku (Japan) | 49168 bytes (193 pages) | 29474 bytes (116 pages) | compression needed |
| Igo Meikan (Japan) | 40976 bytes (161 pages) | 28922 bytes (113 pages) | compression needed |
| Ikinari Musician (Japan) | 49168 bytes (193 pages) | 26965 bytes (106 pages) | compression needed |
| Ikki (Japan) | 24592 bytes (97 pages) | 19057 bytes (75 pages) | compression not needed |
| Joust (USA) | 32784 bytes (129 pages) | 21809 bytes (86 pages) | compression needed |
| Karateka (Japan) | 24592 bytes (97 pages) | 16671 bytes (66 pages) | compression not needed |
| Kekkyoku Nankyoku Daibouken (Japan) (Rev 1) | 24592 bytes (97 pages) | 18143 bytes (71 pages) | compression not needed |
| Kidou Senshi Z Gundam - Hot Scramble (Japan) (Final Version) | 40976 bytes (161 pages) | 28575 bytes (112 pages) | compression needed |
| Lode Runner (USA) | 24592 bytes (97 pages) | 18782 bytes (74 pages) | compression not needed |
| Lot Lot (Japan) | 40976 bytes (161 pages) | 22436 bytes (88 pages) | compression needed |
| Lunar Pool (USA) | 24592 bytes (97 pages) | 18647 bytes (73 pages) | compression not needed |
| M.U.S.C.L.E. - Tag Team Match (USA) | 24592 bytes (97 pages) | 17481 bytes (69 pages) | compression not needed |
| Mach Rider (Japan, USA) (En) (Rev 1) | 40976 bytes (161 pages) | 29683 bytes (116 pages) | compression needed |
| Magmax (USA) | 40976 bytes (161 pages) | 29090 bytes (114 pages) | compression needed |
| Mahjong (Japan) (Rev 2) | 24592 bytes (97 pages) | 18522 bytes (73 pages) | compression not needed |
| Mappy (Japan) | 24592 bytes (97 pages) | 17630 bytes (69 pages) | compression not needed |
| Mario Bros. (World) | 24592 bytes (97 pages) | 18979 bytes (75 pages) | compression not needed |
| Millipede (USA) | 24592 bytes (97 pages) | 17561 bytes (69 pages) | compression not needed |
| Ms. Pac-Man (USA) (Namco) | 40976 bytes (161 pages) | 20121 bytes (79 pages) | compression needed |
| Ninja Hattori-kun - Ninja wa Syugyou de Gozaru no Maki (Japan) | 40976 bytes (161 pages) | 30303 bytes (119 pages) | compression needed |
| Ninja Jajamaru-kun (Japan) | 32784 bytes (129 pages) | 23309 bytes (92 pages) | compression needed |
| Ninja-kun - Majou no Bouken (Japan) (Rev 1) | 24592 bytes (97 pages) | 16295 bytes (64 pages) | compression not needed |
| Nuts & Milk (Japan) | 24592 bytes (97 pages) | 16118 bytes (63 pages) | compression not needed |
| Onyanko Town (Japan) | 40976 bytes (161 pages) | 25642 bytes (101 pages) | compression needed |
| Othello (USA) | 40976 bytes (161 pages) | 20131 bytes (79 pages) | compression needed |
| Pac-Land (Japan) | 40976 bytes (161 pages) | 26544 bytes (104 pages) | compression needed |
| Pac-Man (USA) (Namco) | 24592 bytes (97 pages) | 13114 bytes (52 pages) | compression not needed |
| Pachicom (Japan) | 40976 bytes (161 pages) | 27651 bytes (109 pages) | compression needed |
| Peepar Time (Japan) | 49168 bytes (193 pages) | 31158 bytes (122 pages) | compression needed |
| Penguin-kun Wars (Japan) | 40976 bytes (161 pages) | 25359 bytes (100 pages) | compression needed |
| Pinball (Japan, USA) (En) | 24592 bytes (97 pages) | 18133 bytes (71 pages) | compression not needed |
| Pooyan (Japan) | 24592 bytes (97 pages) | 17640 bytes (69 pages) | compression not needed |
| Popeye (World) (Rev 1) | 24592 bytes (97 pages) | 18894 bytes (74 pages) | compression not needed |
| Popeye no Eigo Asobi (Japan) | 24592 bytes (97 pages) | 19186 bytes (75 pages) | compression not needed |
| Portopia Renzoku Satsujin Jiken (Japan) | 40976 bytes (161 pages) | 30468 bytes (120 pages) | compression needed |
| Raid on Bungeling Bay (USA) | 24592 bytes (97 pages) | 18712 bytes (74 pages) | compression not needed |
| Road Fighter (Europe) | 24592 bytes (97 pages) | 18785 bytes (74 pages) | compression not needed |
| Route-16 Turbo (Japan) | 40976 bytes (161 pages) | 25005 bytes (98 pages) | compression needed |
| Sansuu 1 Nen - Keisan Game (Japan) | 40976 bytes (161 pages) | 18270 bytes (72 pages) | compression needed |
| Sansuu 2 Nen - Keisan Game (Japan) | 40976 bytes (161 pages) | 28230 bytes (111 pages) | compression needed |
| Sansuu 3 Nen - Keisan Game (Japan) | 40976 bytes (161 pages) | 20678 bytes (81 pages) | compression needed |
| Seicross (USA) | 40976 bytes (161 pages) | 26467 bytes (104 pages) | compression needed |
| Sky Destroyer (Japan) | 24592 bytes (97 pages) | 18383 bytes (72 pages) | compression not needed |
| Slalom (USA) | 40976 bytes (161 pages) | 27724 bytes (109 pages) | compression needed |
| Soccer (Japan, USA) (En) | 40976 bytes (161 pages) | 31194 bytes (122 pages) | compression needed |
| Son Son (Japan) (En) | 40976 bytes (161 pages) | 25262 bytes (99 pages) | compression needed |
| Space Invaders (Japan) | 24592 bytes (97 pages) | 10060 bytes (40 pages) | compression not needed |
| Spelunker (USA) | 40976 bytes (161 pages) | 24932 bytes (98 pages) | compression needed |
| Spy vs Spy (USA) | 40976 bytes (161 pages) | 29459 bytes (116 pages) | compression needed |
| Sqoon (USA) | 40976 bytes (161 pages) | 28541 bytes (112 pages) | compression needed |
| Stack-Up (World) | 40976 bytes (161 pages) | 26781 bytes (105 pages) | compression needed |
| Star Force (USA) | 65552 bytes (257 pages) | 30151 bytes (118 pages) | compression needed |
| Star Luster (Japan) | 40976 bytes (161 pages) | 27301 bytes (107 pages) | compression needed |
| Super Arabian (Japan) | 24592 bytes (97 pages) | 17377 bytes (68 pages) | compression not needed |
| Tag Team Wrestling (USA) | 40976 bytes (161 pages) | 31445 bytes (123 pages) | compression needed |
| Tennis (Japan, USA) (En) | 24592 bytes (97 pages) | 19040 bytes (75 pages) | compression not needed |
| Tetris (Bulletproof) (Japan) (Rev 2) | 49168 bytes (193 pages) | 28076 bytes (110 pages) | compression needed |
| Tetris (USA) | 49168 bytes (193 pages) | 28623 bytes (112 pages) | compression needed |
| Thexder (Japan) | 40976 bytes (161 pages) | 19744 bytes (78 pages) | compression needed |
| Urban Champion (World) | 24592 bytes (97 pages) | 17440 bytes (69 pages) | compression not needed |
| Videomation (USA) | 32784 bytes (129 pages) | 20254 bytes (80 pages) | compression needed |
| Volguard II (Japan) (En) | 40976 bytes (161 pages) | 30506 bytes (120 pages) | compression needed |
| Volleyball (USA, Europe) | 40976 bytes (161 pages) | 23453 bytes (92 pages) | compression needed |
| Warpman (Japan) (En) (Rev 1) (Namcot Collection) | 24592 bytes (97 pages) | 15851 bytes (62 pages) | compression not needed |
| Wild Gunman (Japan, USA) (En) | 24592 bytes (97 pages) | 18662 bytes (73 pages) | compression not needed |
| Wrecking Crew (World) | 40976 bytes (161 pages) | 30430 bytes (119 pages) | compression needed |
| Xevious - The Avenger (USA) | 40976 bytes (161 pages) | 27686 bytes (109 pages) | compression needed |
| Yie Ar Kung-Fu (Japan) (Rev 1.4) | 24592 bytes (97 pages) | 19141 bytes (75 pages) | compression not needed |
| Zippy Race (Japan) | 24592 bytes (97 pages) | 17270 bytes (68 pages) | compression not needed |
