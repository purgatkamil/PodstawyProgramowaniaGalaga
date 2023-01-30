#include "primlib.h"
#include <stdlib.h>

struct apple {
	int is_shooting;
	int x_apple;
	int y_apple;
	int apple_speed;
	int apple_size;
	enum color c;
};

struct target {
  int x_target;
  int y_target;
  int x_speed;
  int y_speed;
  int size;
  int health;
  int is_shooting;
  int target_direction_x;
  int target_direction_y;
  enum color c;
};

struct arrow {
	int arrow_is_shooting;
	int x_arrow_coordinates;
	int y_arrow_coordinates;
	int arrow_speed;
	int arrow_distance;
	enum color c;
};

void display_target(const struct target *ptr) {
  gfx_filledCircle(ptr->x_target - ptr->size - 17, ptr->y_target - ptr->size - 5,
                   10, RED); // jablko
  gfx_filledCircle(ptr->x_target - ptr->size - 3, ptr->y_target - ptr->size - 5,
                   10, RED);
  gfx_filledRect(ptr->x_target - ptr->size - 11, ptr->y_target - ptr->size - 8,
                 ptr->x_target - ptr->size - 9, ptr->y_target - ptr->size - 18,
                 RED);
  gfx_filledTriangle(
      ptr->x_target - ptr->size - 10, ptr->y_target - ptr->size - 18,
      ptr->x_target - ptr->size - 5, ptr->y_target - ptr->size - 25, // lisc
      ptr->x_target - ptr->size - 2, ptr->y_target - ptr->size - 20, GREEN);
  gfx_filledTriangle(
      ptr->x_target - ptr->size + 4, ptr->y_target - ptr->size - 27,
      ptr->x_target - ptr->size - 5, ptr->y_target - ptr->size - 25,
      ptr->x_target - ptr->size - 2, ptr->y_target - ptr->size - 20, GREEN);

  gfx_filledCircle(ptr->x_target - ptr->size + 10, ptr->y_target - ptr->size,
                   10, RED); // jablko
  gfx_filledCircle(ptr->x_target - ptr->size + 30, ptr->y_target - ptr->size,
                   10, RED);
  gfx_filledRect(ptr->x_target - ptr->size + 19, ptr->y_target - ptr->size - 3,
                 ptr->x_target - ptr->size + 21, ptr->y_target - ptr->size - 13,
                 RED);
  gfx_filledTriangle(
      ptr->x_target - ptr->size + 20, ptr->y_target - ptr->size - 13,
      ptr->x_target - ptr->size + 25, ptr->y_target - ptr->size - 20, // lisc
      ptr->x_target - ptr->size + 28, ptr->y_target - ptr->size - 15, GREEN);
  gfx_filledTriangle(
      ptr->x_target - ptr->size + 34, ptr->y_target - ptr->size - 22,
      ptr->x_target - ptr->size + 25, ptr->y_target - ptr->size - 20,
      ptr->x_target - ptr->size + 28, ptr->y_target - ptr->size - 15, GREEN);

  gfx_filledRect(ptr->x_target - ptr->size - 50, ptr->y_target - ptr->size,
                   ptr->x_target - ptr->size + 50, ptr->y_target - ptr->size + 40, ptr->c); // jablko
  gfx_circle(ptr->x_target - ptr->size, ptr->y_target - ptr->size, 40, ptr->c);
}

void display_apple(const struct apple *pap){
	  gfx_filledCircle(pap->x_apple - pap->apple_size, pap->y_apple - pap->apple_size,
	                   pap->apple_size, pap->c); // jablko
	  gfx_filledCircle(pap->x_apple - pap->apple_size + 20, pap->y_apple - pap->apple_size,
	                   pap->apple_size, pap->c);
	  gfx_filledRect(pap->x_apple - pap->apple_size + 9, pap->y_apple - pap->apple_size - 17,
	                 pap->x_apple - pap->apple_size + 11, pap->y_apple - pap->apple_size - 27,
	                 RED);
	  gfx_filledTriangle(
	      pap->x_apple - pap->apple_size + 10, pap->y_apple- pap->apple_size - 23,
	      pap->x_apple - pap->apple_size + 15, pap->y_apple - pap->apple_size - 30, // lisc
	      pap->x_apple - pap->apple_size + 18, pap->y_apple - pap->apple_size - 25, GREEN);
	  gfx_filledTriangle(
	      pap->x_apple - pap->apple_size + 24, pap->y_apple - pap->apple_size - 32,
	      pap->x_apple - pap->apple_size + 15, pap->y_apple - pap->apple_size - 30,
	      pap->x_apple - pap->apple_size + 18, pap->y_apple - pap->apple_size - 25, GREEN);
}
  

void bounce(struct target *ptr) {
  ptr->x_target += ptr->target_direction_x * ptr->x_speed;
  if (ptr->x_target <= 0 || ptr->x_target >= gfx_screenWidth()) {
    ptr->target_direction_x *= -1;
  }
  ptr->y_target += ptr->target_direction_y * ptr->y_speed;
  if (ptr->y_target <= 0) {
    ptr->target_direction_y = 1;
  }
  ptr->y_target += ptr->target_direction_y * ptr->y_speed;
  if (ptr->y_target >= gfx_screenHeight() * 0.35) {
    ptr->target_direction_y = -1;
  }
  if (ptr->y_target >= (gfx_screenHeight() + 50)) {
    ptr->y_target= -100;
  }
}

int main() {
  if (gfx_init())
    exit(3);
  
  int level = 1;
  int number_of_targets = level;

  int damage_distance = 80;

  int score = 0;
  int health = 3;

  int on_hold = 0;

  double hit_distance = 45;
  double apple_hit_distance = 30;

  int cannon_x = 0;


  //struct target td[3];
  struct target *td = malloc(level * sizeof(*td));

for(int i = 0; i < level; ++i){
  td[i].x_target = 150;
  td[i].y_target = -100;
  td[i].target_direction_x = 1;
  td[i].target_direction_y = 1;
  td[i].size = 20;
  td[i].c = YELLOW;
  td[i].x_speed = 3;
  td[i].y_speed = 1;
  td[i].health = 3;
  td[i].is_shooting = 1;
  }

  /*td[1].x_target = 1;
  td[1].y_target = -100;
  td[1].target_direction_x = 1;
  td[1].target_direction_y = -1;
  td[1].size = 20;
  td[1].c = YELLOW;
  td[1].x_speed = 4;
  td[1].y_speed = 1.8;
  td[1].health = 3;
  td[1].is_shooting = 1;

  td[2].x_target = gfx_screenWidth();
  td[2].y_target = -100;
  td[2].target_direction_x = -1;
  td[2].target_direction_y = -1;
  td[2].size = 20;
  td[2].c = YELLOW;
  td[2].x_speed = 5;
  td[2].y_speed = 2.5;
  td[2].health = 3;
  td[2].is_shooting = 1;*/


  struct apple app[5];

  app[0].is_shooting = 0;
  app[0].x_apple = td[0].x_target;
  app[0].y_apple = td[0].y_target;
  app[0].apple_speed = 4;
  app[0].apple_size = 20;
  app[0].c = RED;

  app[1].is_shooting = 0;
  app[1].x_apple = td[1].x_target;
  app[1].y_apple = td[1].y_target;
  app[1].apple_speed = 4;
  app[1].apple_size = 20;
  app[1].c = RED;

  app[2].is_shooting = 0;
  app[2].x_apple = td[2].x_target;
  app[2].y_apple = td[2].y_target;
  app[2].apple_speed = 4;
  app[2].apple_size = 20;
  app[2].c = RED;

  app[3].is_shooting = 0;
  app[3].x_apple = td[3].x_target;
  app[3].y_apple = td[3].y_target;
  app[3].apple_speed = 4;
  app[3].apple_size = 20;
  app[3].c = RED;

  app[4].is_shooting = 0;
  app[4].x_apple = td[4].x_target;
  app[4].y_apple = td[4].y_target;
  app[4].apple_speed = 4;
  app[4].apple_size = 20;
  app[4].c = RED;


  struct arrow arr[3];

  arr[0].arrow_is_shooting = 0;
  arr[0].arrow_speed = 0;
  arr[0].arrow_distance = 100;
  arr[0].x_arrow_coordinates = (gfx_screenWidth() / 2) + cannon_x;
  arr[0].y_arrow_coordinates = gfx_screenHeight() - arr[0].arrow_distance + arr[0].arrow_speed;

  arr[1].arrow_is_shooting = 0;
  arr[1].arrow_speed = 0;
  arr[1].arrow_distance = 100;
  arr[1].x_arrow_coordinates = (gfx_screenWidth() / 2) + cannon_x;
  arr[1].y_arrow_coordinates = gfx_screenHeight() - arr[0].arrow_distance + arr[1].arrow_speed;

  arr[2].arrow_is_shooting = 0;
  arr[2].arrow_speed = 0;
  arr[2].arrow_distance = 100;
  arr[2].x_arrow_coordinates = (gfx_screenWidth() / 2) + cannon_x;
  arr[2].y_arrow_coordinates = gfx_screenHeight() - arr[0].arrow_distance + arr[2].arrow_speed;

  while (1) {

  	for (int i = 0; i < sizeof(app) / sizeof(app[0]); ++i){	
  		if(app[i].is_shooting == 0){
  			app[i].x_apple = td[i].x_target;
		  	app[i].y_apple = td[i].y_target;
  		}
  	}

	  	for (int i = 0; i < sizeof(app) / sizeof(app[0]); ++i){		  	
		  	if(app[i].is_shooting == 0){
		  		if(rand() % 80 == 1){
		  	  		app[i].is_shooting = 1;
		  	  	}
		  	}
	  	}

	  for (int i = 0; i < level; ++i){	  		
	  		if(app[i].is_shooting == 1){
	  			app[i].x_apple = td[i].x_target;
	  			app[i].y_apple +=5;
	  		}
	  }

	  for (int i = 0; i < level; ++i){	  		
	  		if(app[i].y_apple >= gfx_screenHeight() && app[i].is_shooting == 1){
	  			app[i].is_shooting = 0;
	  		}
	  }

  	  for (int i = 0; i < level; ++i){
	  if(td[i].health == 3){
	  	td[i].c = YELLOW;
	  }
	  else if(td[i].health == 2){
	  	td[i].c = ORANGE;
	  }
	  else if(td[i].health == 1){
	  	td[i].c = TOMATO;
	  }
	  else{
	  		if(td[i].health == 0 && td[i].is_shooting == 1){
	  			number_of_targets--;
	  		}
	  	td[i].is_shooting = 0;
	  	td[i].x_target = -200;
	  	td[i].y_target = -200;
	  }
   }

  	char points[20];
  	sprintf(points, "PUNKTY: %d", score);

  	char target_health[30];
  	sprintf(target_health, "POZIOM: %d", /*app[0].is_shooting*/ level);

  	//char target_health2[20];
  	//sprintf(target_health2, "TRAFIENIA: %d", /*app[1].is_shooting*/ number_of_targets);

  	//char target_health3[20];
  	//sprintf(target_health3, "TRAFIENIA: %d", app[2].is_shooting);

  		gfx_filledRect(0, 0, gfx_screenWidth() - 1, gfx_screenHeight() - 1,
	                   BLACK); // tlo
	    gfx_filledRect(0, gfx_screenHeight() - 100, gfx_screenWidth() - 1,
	                   gfx_screenHeight() - 1, BLACK);
  	


    for (int i = 0; i <= 10; ++i) // dzialo
    {
      gfx_circle((gfx_screenWidth() / 2 + cannon_x), (gfx_screenHeight() - 25),
                 (100 - i), WHITE);
    }
    gfx_filledRect(
        (gfx_screenWidth() / 2 + cannon_x - 100), (gfx_screenHeight() - 50),
        (gfx_screenWidth() / 2 + cannon_x + 100), gfx_screenHeight(), BLACK);

    if (on_hold == 0) {
      gfx_line((gfx_screenWidth() / 2 + cannon_x - 99),
               (gfx_screenHeight() - 50),
               (gfx_screenWidth() / 2 + cannon_x + 99),
               (gfx_screenHeight() - 50), WHITE);
    }
    if (on_hold == 1) {
      gfx_line((gfx_screenWidth() / 2 + cannon_x - 99),
               (gfx_screenHeight() - 50), gfx_screenWidth() / 2 + cannon_x,
               gfx_screenHeight() - 1, RED);
      gfx_line((gfx_screenWidth() / 2 + cannon_x + 99),
               (gfx_screenHeight() - 50), gfx_screenWidth() / 2 + cannon_x,
               gfx_screenHeight() - 1, RED);
    }


	for (int i = 0; i < sizeof(app) / sizeof(app[0]); ++i){ 		//jablka
	    if(app[i].is_shooting == 1){
	      	display_apple(&(app[i]));
	  	}
	}
    
	for (int i = 0; i < level; ++i){ 		//kosze
	    if(td[i].is_shooting == 1){
	      	display_target(&(td[i]));
	  	}
	}


  	for (int a = 0; a < sizeof(arr) / sizeof(arr[0]); ++a){
    if (arr[a].arrow_is_shooting == 1) // pocisk
    {
      arr[a].y_arrow_coordinates =
          gfx_screenHeight() - arr[a].arrow_distance + arr[a].arrow_speed;
      gfx_filledRect(arr[a].x_arrow_coordinates - 1, arr[a].y_arrow_coordinates - 50,
                     arr[a].x_arrow_coordinates + 1, arr[a].y_arrow_coordinates + 50,
                     WHITE);
      gfx_filledTriangle(arr[a].x_arrow_coordinates - 4, arr[a].y_arrow_coordinates - 50,
                         arr[a].x_arrow_coordinates + 4, arr[a].y_arrow_coordinates - 50,
                         arr[a].x_arrow_coordinates, arr[a].y_arrow_coordinates - 65,
                         WHITE);
      gfx_line(arr[a].x_arrow_coordinates - 1, arr[a].y_arrow_coordinates + 50,
               arr[a].x_arrow_coordinates - 10, arr[a].y_arrow_coordinates + 65, WHITE);
      gfx_line(arr[a].x_arrow_coordinates - 1, arr[a].y_arrow_coordinates + 50,
               arr[a].x_arrow_coordinates + 10, arr[a].y_arrow_coordinates + 65, WHITE);
      gfx_line(arr[a].x_arrow_coordinates - 1, arr[a].y_arrow_coordinates + 50,
               arr[a].x_arrow_coordinates, arr[a].y_arrow_coordinates + 70, WHITE);
    } else if (on_hold == 0) {
      gfx_filledRect((gfx_screenWidth() / 2 + cannon_x - 1),
                     (gfx_screenHeight() - 170),
                     (gfx_screenWidth() / 2 + cannon_x + 1),
                     (gfx_screenHeight() - 50), WHITE);
      gfx_filledTriangle(
          (gfx_screenWidth() / 2 + cannon_x - 4), (gfx_screenHeight() - 170),
          (gfx_screenWidth() / 2 + cannon_x + 4), (gfx_screenHeight() - 170),
          (gfx_screenWidth() / 2 + cannon_x), (gfx_screenHeight() - 185),
          WHITE);
      gfx_line((gfx_screenWidth() / 2 + cannon_x - 1),
               (gfx_screenHeight() - 50),
               (gfx_screenWidth() / 2 + cannon_x - 11),
               (gfx_screenHeight() - 40), WHITE);
      gfx_line((gfx_screenWidth() / 2 + cannon_x - 1),
               (gfx_screenHeight() - 50),
               (gfx_screenWidth() / 2 + cannon_x + 11),
               (gfx_screenHeight() - 40), WHITE);
      gfx_line((gfx_screenWidth() / 2 + cannon_x - 1),
               (gfx_screenHeight() - 50), (gfx_screenWidth() / 2 + cannon_x),
               (gfx_screenHeight() - 35), WHITE);

    } else {
      gfx_filledRect(
          (gfx_screenWidth() / 2 + cannon_x - 1), (gfx_screenHeight() - 125),
          (gfx_screenWidth() / 2 + cannon_x + 1), (gfx_screenHeight()), WHITE);
      gfx_filledTriangle(
          (gfx_screenWidth() / 2 + cannon_x - 4), (gfx_screenHeight() - 125),
          (gfx_screenWidth() / 2 + cannon_x + 4), (gfx_screenHeight() - 125),
          (gfx_screenWidth() / 2 + cannon_x), (gfx_screenHeight() - 140),
          WHITE);
    }
	}

    gfx_textout(10, 10, points, WHITE);
    gfx_textout(150, 10, target_health, WHITE);
    //gfx_textout(400, 10, target_health2, WHITE);
    if(number_of_targets == 0){
    	struct target *td2;
	  	td2 = realloc(td, (level + 1) * sizeof(struct target));
	  	if(!td2){
	  		printf("Problem z alokacja pamieci.");
        free(td);
	  		break;
	  	}
	  	else{
	  		level++;
	  		number_of_targets = level;
	  		td = td2;	  		
	  		score += 50;
	  		
	  		for(int i = 0; i < level; ++i){
				td[i].x_target = rand() % gfx_screenWidth();
				td[i].y_target = -(rand() % 100);
				td[i].target_direction_x = 1;
				td[i].target_direction_y = 1;
				td[i].size = 20;
				td[i].c = YELLOW;
				td[i].x_speed = (2 * (1.3 * i) + 1);
				td[i].y_speed = i + 1;
				td[i].health = 3;
				td[i].is_shooting = 1;
  			}

	  	}
	 }

    if(health > 0){
    	gfx_filledTriangle(8, 35, 37, 35, 22.5, 47, BLACK);
    	gfx_filledTriangle(8, 35, 24.5, 35, 16.25, 27, BLACK);
    	gfx_filledTriangle(20.5, 35, 37, 35, 28.75, 27, BLACK);
    	gfx_filledTriangle(10, 35, 35, 35, 22.5, 45, RED);
    	gfx_filledTriangle(10, 35, 22.5, 35, 16.25, 29, RED);
    	gfx_filledTriangle(22.5, 35, 35, 35, 28.75, 29, RED);
    }

    if(health > 1){
	    gfx_filledTriangle(38, 35, 67, 35, 52.5, 47, BLACK);
	    gfx_filledTriangle(38, 35, 54.5, 35, 46.25, 27, BLACK);
	    gfx_filledTriangle(50.5, 35, 67, 35, 58.75, 27, BLACK);
	    gfx_filledTriangle(40, 35, 65, 35, 52.5, 45, RED);
	    gfx_filledTriangle(40, 35, 52.5, 35, 46.25, 29, RED);
	    gfx_filledTriangle(52.5, 35, 65, 35, 58.75, 29, RED);
	}
	if(health > 2){
	    gfx_filledTriangle(68, 35, 97, 35, 82.5, 47, BLACK);
	    gfx_filledTriangle(68, 35, 84.5, 35, 76.25, 27, BLACK);
	    gfx_filledTriangle(80.5, 35, 97, 35, 88.75, 27, BLACK);
	    gfx_filledTriangle(70, 35, 95, 35, 82.5, 45, RED);
	    gfx_filledTriangle(70, 35, 82.5, 35, 76.25, 29, RED);
	    gfx_filledTriangle(82.5, 35, 95, 35, 88.75, 29, RED);
	}
	if(health == 0){
		gfx_filledRect(0, 0, gfx_screenWidth(), gfx_screenHeight(), BLACK);
		gfx_textout((gfx_screenWidth() / 2) - 40, (gfx_screenHeight() / 2) - 5, "KONIEC GRY", WHITE);
    if(!td){
    free(td);
    }
	}
	if(level == 6){
		gfx_filledRect(0, 0, gfx_screenWidth(), gfx_screenHeight(), BLACK);
		gfx_textout((gfx_screenWidth() / 2) - 40, (gfx_screenHeight() / 2) - 5, "YOU WIN!", WHITE);
		if(!td){
		free(td);
		}
	}

    gfx_updateScreen();

for (int a = 0; a < sizeof(arr) / sizeof(arr[0]); ++a){
    if (arr[a].x_arrow_coordinates > gfx_screenWidth() || arr[a].x_arrow_coordinates < 0 ||
      arr[a].y_arrow_coordinates < 0) {
      arr[a].arrow_is_shooting = 0;
      arr[a].arrow_distance = 100;
      arr[a].arrow_speed = 0;
			 // wykrywanie przekroczenia ekranu przez pocisk
    }
   }
for (int a = 0; a < sizeof(arr) / sizeof(arr[0]); ++a){
    if (arr[a].arrow_is_shooting == 1) {
      arr[a].arrow_speed -= 5;

      for(int i = 0; i < level;
           ++i){ // wykrywanie trafienia celu
        if (hypot(arr[a].x_arrow_coordinates - td[i].x_target,
                  (arr[a].y_arrow_coordinates - 65) - td[i].y_target) <
            hit_distance) {
            arr[a].arrow_is_shooting = 0;
            arr[a].arrow_distance = 100;
            arr[a].arrow_speed = 0;
            td[i].health -= 1;
            if(td[i].health == 0){
            	score += 10;
            	app[i].is_shooting = 0; 
        	}
            else{
            	score += 2;
            }          
            if(td[i].health == 0){
            td[i].x_target = rand() % gfx_screenWidth();
            td[i].y_target = -(rand() % 100);
        	}          
        }
    }
        for(int i = 0; i < level;
           ++i){ 
        if (hypot(arr[a].x_arrow_coordinates - app[i].x_apple,
                  (arr[a].y_arrow_coordinates - 65) - app[i].y_apple) <
            apple_hit_distance) {
            arr[a].arrow_is_shooting = 0;
            arr[a].arrow_distance = 100;
            arr[a].arrow_speed = 0;
            app[i].is_shooting = 0;
            score += 1;         
            if(td[i].health == 0){
            td[i].x_target = rand() % gfx_screenWidth();
            td[i].y_target = -(rand() % 100);
        }
    }
          
        }
    }
}
for (int i = 0; i < sizeof(app) / sizeof(app[0]); ++i){
	if(app[i].y_apple > 0){
		if (hypot((gfx_screenWidth() / 2 + cannon_x)- app[i].x_apple,
                  (gfx_screenHeight() - 25) - app[i].y_apple) < damage_distance){	
			app[i].is_shooting = 0;
			app[i].x_apple = td[i].x_target;
			app[i].y_apple = td[i].y_target;
	        --health;
		}
	}
}

    for (int i = 0; i < level;
         ++i) // warunki odbijania celow
      bounce(&(td[i]));

    if (gfx_isKeyDown(SDLK_RIGHT)) {
      if ((gfx_screenWidth() / 2 + cannon_x) < gfx_screenWidth()) {
        cannon_x += 6;
      }
    }
    if (gfx_isKeyDown(SDLK_LEFT)) {
      if ((gfx_screenWidth() / 2 + cannon_x) > 0) {
        cannon_x -= 6;
      }
    }

    if (gfx_isKeyDown(SDLK_SPACE)) {
      on_hold = 1;
    } else {
    
      if (arr[0].arrow_is_shooting == 0 && on_hold == 1) {
        arr[0].arrow_is_shooting = 1;
        arr[0].arrow_distance = 100.0;
        arr[0].x_arrow_coordinates = (gfx_screenWidth() / 2) + cannon_x;
      }
      else if(arr[1].arrow_is_shooting == 0 && on_hold == 1){
      	arr[1].arrow_is_shooting = 1;
        arr[1].arrow_distance = 100.0;
        arr[1].x_arrow_coordinates = (gfx_screenWidth() / 2) + cannon_x;
      }
      else if(arr[2].arrow_is_shooting == 0 && on_hold == 1){
      	arr[2].arrow_is_shooting = 1;
        arr[2].arrow_distance = 100.0;
        arr[2].x_arrow_coordinates = (gfx_screenWidth() / 2) + cannon_x;
      }
  	
      on_hold = 0;
    }

    SDL_Delay(15);
  }
  return 0;
}
