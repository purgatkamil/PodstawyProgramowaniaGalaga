# PodstawyProgramowaniaGalaga
Gra Galaga w języku C z wykorzystaniem prostej biblioteki graficznej

Do stworzenia gry zostały wykorzystane struktury. Część z nich jest dynamicznie alokowana. Do większości funkcji parametry są przekazywane przy pomocy wskaźników.
Całość pisana była na systemie Ubuntu z wykorzystaniem biblioteki primlib, która z kolei wykorzystuje bibliotekę SDL_gfx.

Aby pobrać repozytorium zawierające podstawowe pliki, przykłady z wykorzystania funkcji oraz szablony, które należało wykorzystać do rozbudowy programu
trzeba w konsoli wpisać poniższą komendę:

  git clone https://gitlab.dmcs.pl/gwj/graphics_tutorial.git

oraz zainstalować odpowiednie rozszerzenie przy pomocy poniższej komendy:

  sudo apt install libsdl2-gfx-dev
  
Do kompilacji programów przy użyciu biblioteki można użyć następującej komendy:
  
  gcc -g -Wall -pedantic `sdl2-config --cflags` primlib.c progname.c -o progname -lSDL2_gfx `sdl2-config --libs`
  
progname.c to nazwa głównego modułu programu.


