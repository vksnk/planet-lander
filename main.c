#include "SDL.h"
#include <stdio.h>
#include <stdlib.h>
#include "SDL_opengl.h"
#include <math.h>
#include <time.h>
#include <sys/time.h>

#ifdef __APPLE__
    #include <OpenGL/glu.h>
    #include <OpenGL/glext.h>
#else
    #include <GL/glu.h>
    #include <GL/glext.h>
    #include <GL/glx.h>
    #include <GL/glxext.h>
    #define glXGetProcAddress(x) (*glXGetProcAddressARB)((const GLubyte*)x)
#endif

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const int SCREEN_BPP = 32;

const int ship_size = 5;
#define planet_detalization 51
#define particles_of_destroyed_ship 50
#define CRASH_SPEED_THRESHOLD 1.3
#define LANDED_SPEED_THRESHOLD 0.01

struct Ship_s {
	float x;
	float y;
	float angle;

	float speed_x;
	float speed_y;

	char throtle;
	float particles[particles_of_destroyed_ship][4];
	int destroyed;
	int landed;

	float weight;
	int fuel;
};

struct PlanetSurface_s {
	int dots[planet_detalization + 1];
};

struct Planet1 {
	float x, y;
	float speed_x, speed_y;
	float weight;
	float radius;
};

struct Star {
	float x,y;
	float weight;
	float radius;
};

#define PLANETS_NUMBER 5
typedef struct {
	struct Planet1 planets[PLANETS_NUMBER];
	struct Star star;
} SolarSystem;

typedef struct Ship_s Ship;
typedef struct PlanetSurface_s Planet;


struct Game {
	Ship ship;
	Planet planet;
	int stage;
	int timer;
};

void generate_solar_system(SolarSystem *solar_system)
{
	solar_system->star.x = SCREEN_WIDTH/2;
	solar_system->star.y = SCREEN_HEIGHT/2;
	solar_system->star.radius = 20;
	solar_system->star.weight = 1000000;

	for (int i=0; i<PLANETS_NUMBER; i++) {
		solar_system->planets[i].radius = 3 + rand()%10;
		solar_system->planets[i].weight = solar_system->planets[i].radius * solar_system->planets[i].radius * solar_system->planets[i].radius;
		solar_system->planets[i].x = rand() % SCREEN_HEIGHT;
		solar_system->planets[i].y = rand() % SCREEN_HEIGHT;
		// solar_system->planets[i].speed_x;
	}
}

void generate_planet(Planet *planet)
{
	srand(0);
	for (int i=0; i < planet_detalization + 1; i++) {
		planet->dots[i] = SCREEN_HEIGHT - 60 + rand()%55;
	}
	for (int i=0; i<3; i++) {
		int n = rand() % planet_detalization;
		for (int j=n; j< n+rand() % (planet_detalization/5); j++) {
			planet->dots[j] = planet->dots[n];
		}
	}
}

//      *
//     * *
//    *   *
//   *     *
//  *   *   *
// * *     * *
int draw_ship(const Ship ship)
{
	if (ship.destroyed) {
		glBegin(GL_POINTS);
		for (int i=0; i<particles_of_destroyed_ship; i++) {
			glVertex3f(ship.particles[i][0], ship.particles[i][1], 0.0);
		}
		glEnd();
	} else {
		glLineWidth(0.4);
		glColor3f(1.0, 1.0, 1.0);

		glBegin(GL_LINE_STRIP);

		// glVertex3f(ship.x, ship.y, 0.0);
		glVertex3f(ship.x + ship_size * sin(ship.angle), ship.y + ship_size * cos(ship.angle), 0.0);
		glVertex3f(ship.x + ship_size * sin(ship.angle + 3*M_PI/4), ship.y + ship_size * cos(ship.angle+ 3*M_PI/4), 0.0);
		glVertex3f(ship.x + ship_size/4 * sin(ship.angle + 4*M_PI/4), ship.y + ship_size/4 * cos(ship.angle+ 4*M_PI/4), 0.0);
		glVertex3f(ship.x + ship_size * sin(ship.angle + 5*M_PI/4), ship.y + ship_size * cos(ship.angle+ 5*M_PI/4), 0.0);

		glVertex3f(ship.x + ship_size * sin(ship.angle), ship.y + ship_size * cos(ship.angle), 0.0);
		glEnd();

		if (ship.throtle) {
			glBegin(GL_LINE_STRIP);
			glVertex3f(ship.x + 2*ship_size/3 * sin(ship.angle + 7*M_PI/8), ship.y + 2*ship_size/3 * cos(ship.angle+ 7*M_PI/8), 0.0);
			glVertex3f(ship.x + ship_size * sin(ship.angle + 4*M_PI/4), ship.y + ship_size * cos(ship.angle+ 4*M_PI/4), 0.0);
			glVertex3f(ship.x + 2*ship_size/3 * sin(ship.angle + 9*M_PI/8), ship.y + 2*ship_size/3 * cos(ship.angle+ 9*M_PI/8), 0.0);
			glEnd();
		}
	}
	return 0;
}
void destroy_ship(Ship* ship)
{
	ship->destroyed = 1;
	for (int i = 0; i<particles_of_destroyed_ship; i++) {
		ship->particles[i][0] = ship->x;
		ship->particles[i][1] = ship->y;
		ship->particles[i][2] = 1 - 0.001 * (rand() % 2000);
		ship->particles[i][3] = - 0.002 * (rand() % 1000);
	}
}
int draw_planet_surface(Planet *planet)
{
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < planet_detalization; i++) {
		glVertex3f(i * (SCREEN_WIDTH / ((float)planet_detalization-1)), planet->dots[i], 0.0);
	}
	glEnd();
	return 0;
}
const float DEG2RAD = 3.14159/180;
void draw_circle(float r, float x, float y)
{
	glBegin(GL_LINE_LOOP);

	for (int i=0; i < 360; i++)
	{
		float degInRad = i*DEG2RAD;
		glVertex2f( x + cos(degInRad) * r,
					y + sin(degInRad) * r);
	}
	glEnd();
}
void draw_solar_system(SolarSystem* solar_system)
{
	draw_circle(solar_system->star.radius, solar_system->star.x, solar_system->star.y);
	for (int i=0; i<PLANETS_NUMBER; i++) {
		draw_circle(solar_system->planets[i].radius, solar_system->planets[i].x, solar_system->planets[i].y);
	}
}
void draw_vector_text(const char* text, int x, int y, float font_scale);

void draw_stats(Ship *ship, float fps)
{
	char fuel[100];
	sprintf(fuel, "Fuel: %d", ship->fuel);
	draw_vector_text(fuel, 10, 10, 10);
}

//1 - on left
//0 - on line
//-1 - on right
int is_point_line_position(float line_point1x,
						float line_point1y,
						float line_point2x,
						float line_point2y,
						float point_x,
						float point_y)

{
    int tmp = (line_point2x-line_point1x) * (point_y-line_point1y) -
              (line_point2y-line_point1y) * (point_x-line_point1x);

    if (tmp > 0)
        return 1;
    else
        if (tmp < 0)
            return -1;
        else
            return 0;
}

int calculate_world(Ship *ship, Planet *planet)
{
	//engine
	if (ship->destroyed) {
		for (int i=0; i<particles_of_destroyed_ship; i++) {
			ship->particles[i][0] += ship->particles[i][2];
			ship->particles[i][1] += ship->particles[i][3];

			//gravity
			ship->particles[i][3] += 0.01;
		}
	} else if (!ship->landed) {
		if (ship->throtle) {
			ship->speed_x += 0.08 * sin(ship->angle);
			ship->speed_y += 0.08 * cos(ship->angle);
		}
		//gravity
		ship->speed_y += 0.01;

		ship->y += ship->speed_y;
		ship->x += ship->speed_x;

		if (ship->x >= SCREEN_WIDTH) {
			ship->x -= SCREEN_WIDTH;
		} else if (ship->x < 0) {
			ship->x += SCREEN_WIDTH;
		}

		//collision detection
		//rules: speed > threshold = crash
		//speed < threshold = stop or chage move direction

		float ship_surface[] = {
			ship->x + ship_size * sin(ship->angle),
			ship->y + ship_size * cos(ship->angle),

			ship->x + ship_size * sin(ship->angle + 3*M_PI/4),
			ship->y + ship_size * cos(ship->angle+ 3*M_PI/4),

			ship->x + ship_size/4 * sin(ship->angle + 4*M_PI/4),
			ship->y + ship_size/4 * cos(ship->angle+ 4*M_PI/4),

			ship->x + ship_size * sin(ship->angle + 5*M_PI/4),
			ship->y + ship_size * cos(ship->angle+ 5*M_PI/4)
		};

		for (int d = 0; d < 4; d++) {
			//TODO: evaluate nearest points
			for (int i = 0; i < planet_detalization-1; i++) {
				float line_start_x = i * (SCREEN_WIDTH / ((float)planet_detalization-1));
				float line_end_x = (i+1) * (SCREEN_WIDTH / ((float)planet_detalization-1));

				if (!(line_start_x < ship_surface[2*d] && ship_surface[2*d] <= line_end_x))
					continue;

				if (is_point_line_position(line_start_x, planet->dots[i],
											line_end_x, planet->dots[i+1],
											ship_surface[2*d],
											ship_surface[2*d+1]) == 1)
				{
					if (sqrt(ship->speed_x * ship->speed_x + ship->speed_y * ship->speed_y) > CRASH_SPEED_THRESHOLD) {
						return 1;
					} else {
						float dot_angle = 0;
						if (d == 0) dot_angle = 0;
						if (d == 1) dot_angle = 3*M_PI/4;
						if (d == 2) dot_angle = 4*M_PI/4;
						if (d == 3) dot_angle = 5*M_PI/4;
						ship->y = planet->dots[i] + (planet->dots[i + 1] - planet->dots[i]) * ((ship->x - line_start_x ) / (line_start_x - line_end_x)) - ship_size * cos(dot_angle + ship->angle);
						ship->speed_y = 0;
						ship->speed_x *= 0.7;
					}
					if (sqrt(ship->speed_x * ship->speed_x + ship->speed_y * ship->speed_y) < LANDED_SPEED_THRESHOLD) {
						return -1;
					}
				}
			}
		}
	}
	return 0;
}
void calculate_world_stage1(Ship *ship, SolarSystem *solar_system)
{
	if (ship->destroyed) {
		for (int i=0; i<particles_of_destroyed_ship; i++) {
			ship->particles[i][0] += ship->particles[i][2];
			ship->particles[i][1] += ship->particles[i][3];

			//gravity
			// ship->particles[i][3] += 0.01;
		}
	} else if (!ship->landed) {
		if (ship->throtle) {
			ship->speed_x += 0.08 * sin(ship->angle);
			ship->speed_y += 0.08 * cos(ship->angle);
		}
		//gravity
		float force_x, force_y;


		ship->y += ship->speed_y;
		ship->x += ship->speed_x;

		if (ship->x >= SCREEN_WIDTH) {
			ship->x -= SCREEN_WIDTH;
		} else if (ship->x < 0) {
			ship->x += SCREEN_WIDTH;
		}
		if (ship->y >= SCREEN_HEIGHT) {
			ship->y -= SCREEN_HEIGHT;
		} else if (ship->y < 0) {
			ship->y += SCREEN_HEIGHT;
		}

		//collision
		if (sqrt( pow((ship->x - solar_system->star.x),2) + pow((ship->y - solar_system->star.y),2))
				< solar_system->star.radius) {
			ship->destroyed = 1;
			destroy_ship(ship);
		}
		for (int i=0; i<PLANETS_NUMBER; i++) {
			if (sqrt( pow((ship->x - solar_system->planets[i].x),2) + pow((ship->y - solar_system->planets[i].y),2))
					< solar_system->star.radius) {

				if ( sqrt(pow(ship->speed_x - solar_system->planets[i].speed_x, 2)
						+ pow(ship->speed_y - solar_system->planets[i].speed_y, 2)) > CRASH_SPEED_THRESHOLD) {
					ship->destroyed = 1;
					destroy_ship(ship);
				} else {
					ship->landed = 1;
				}
			}
		}
	}
}

SDL_Surface* screen;
int main( int argc, char* args[] )
{
	srand(time(0));
	SDL_Event event;

	//------------------init--------------------
	if (SDL_Init( SDL_INIT_EVERYTHING) == -1 ) {
		printf("Error in SDL_Init\n");
		return 1;
	}
	SDL_WM_SetCaption("Lander game", NULL);


	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_OPENGL);
	if (screen == NULL) {
		printf("Error in SDL_SetVideoMode");
		return 1;
	}
	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

	glEnable( GL_TEXTURE_2D );
	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );

	glViewport( 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT );

	glClear( GL_COLOR_BUFFER_BIT );

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();

	glOrtho(0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, -1.0f, 1.0f);

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

	glClear(GL_COLOR_BUFFER_BIT);
	SDL_GL_SwapBuffers();
	glClear(GL_COLOR_BUFFER_BIT);


	//-----------------main loop----------------
	Ship ship;
	Planet planet;
	SolarSystem solar_system;
	struct Game game;

	int exit = 0;
	int game_in_porcess = 1;
	float fps = 0;

	while (!exit) {

		generate_solar_system(&solar_system);
		ship.x = 100;
		ship.y = 100;
		ship.angle = M_PI;
		ship.speed_x = 0;
		ship.speed_y = 0;
		ship.throtle = 0;
		ship.destroyed = 0;
		ship.landed = 0;

		while (1) {
			if (SDL_PollEvent(&event)) {
				if (event.type == SDL_QUIT) {
					exit = 1;
					break;
				}
			}
			if (event.type == SDL_KEYDOWN) {
				if (event.key.keysym.sym == SDLK_n){
					if (ship.destroyed || ship.landed)
						break;
				}
			}
			Uint8 *keystates = SDL_GetKeyState( NULL );

			if (!ship.landed) {
				if( keystates[ SDLK_UP ] )
					ship.throtle = 1;
				else
					ship.throtle = 0;
				if( keystates[ SDLK_LEFT ] )
					ship.angle += 0.1;
				if( keystates[ SDLK_RIGHT ] )
					ship.angle -= 0.1;
			}

			calculate_world_stage1(&ship, &solar_system);

			glClear(GL_COLOR_BUFFER_BIT);
			draw_ship(ship);
			draw_solar_system(&solar_system);

			draw_vector_text(" !\"#$%&\'()*+,-./0123456789:;<=>?", 10, 10, 20.0);
			draw_vector_text("@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_", 10, 50, 20.0);
			draw_vector_text("`abcdefghijklmnopqrstuvwxyz{|}~ ", 10, 90, 20.0);

			if (ship.destroyed == 1) {
				draw_vector_text("Ship crashed!", SCREEN_WIDTH/2, 200, 10.0);
				draw_vector_text("Press n for new game", 100, 100, 10.0);
			}
			if (ship.landed) {
				draw_vector_text("WIN!", SCREEN_WIDTH/2, 200, 10.0);
				break;
			}

			SDL_GL_SwapBuffers();

			SDL_Delay(20);
		}
		if (exit) break;

		if (! ship.landed) continue;

		ship.x = SCREEN_WIDTH/2;
		ship.y = SCREEN_HEIGHT/2;
		ship.angle = M_PI;
		ship.speed_x = 0;
		ship.speed_y = 0;
		ship.throtle = 0;
		ship.destroyed = 0;
		ship.landed = 0;

		generate_planet(&planet);

		while (1) {
			if (SDL_PollEvent(&event)) {
				if (event.type == SDL_QUIT) {
					exit = 1;
					break;
				}
			}
			if (event.type == SDL_KEYDOWN) {
				if (event.key.keysym.sym == SDLK_n){
					break;
				}
			}
			Uint8 *keystates = SDL_GetKeyState( NULL );

			if (!ship.landed) {
				if( keystates[ SDLK_UP ] )
					ship.throtle = 1;
				else
					ship.throtle = 0;
				if( keystates[ SDLK_LEFT ] )
					ship.angle += 0.1;
				if( keystates[ SDLK_RIGHT ] )
					ship.angle -= 0.1;
			}

			int current_state = calculate_world(&ship, &planet);
			if ( current_state == 1) {
				destroy_ship(&ship);
			} else if (current_state == -1) {
				ship.landed = 1;
			}

			glClear(GL_COLOR_BUFFER_BIT);
			draw_ship(ship);
			draw_planet_surface(&planet);
			draw_stats(&ship, fps);
			if (ship.destroyed == 1) {
				draw_vector_text("Ship crashed!", SCREEN_WIDTH/2, 200, 10.0);
				draw_vector_text("Press n for new game", 100, 100, 10.0);
			}
			if (ship.landed) {

				draw_vector_text("WIN!", SCREEN_WIDTH/2, 200, 20.0);
			}

			SDL_GL_SwapBuffers();

			SDL_Delay(20);
		}

	}

	SDL_Quit();
	return 0;
}