#include <raylib.h>
#include <raymath.h>
#include <time.h>
#include <math.h>

typedef signed int i32;

#define WIDTH 800
#define HEIGHT 800

#define RADIUS HEIGHT * 0.4

#define SEC_HAND_LEN RADIUS * 0.9
#define SEC_HAND_THICK 10

#define MIN_HAND_LEN RADIUS * 0.8
#define MIN_HAND_THICK 12

#define HOUR_HAND_LEN RADIUS * 0.7
#define HOUR_HAND_THICK 14

#define MARKS_THICK 8

#define MINSEC_ANGLE(n) 2. * PI / 60. * (n)
#define HOUR_ANGLE(n) 2. * PI / 12. * (n)

void DrawClockMarks(Vector2 center) {
	for (i32 i=0; i<60; ++i) {
		float radius = (i % 5 == 0) ? RADIUS*0.9 : RADIUS*0.95;
	
		Vector2 start;
		start.x = center.x + cosf(MINSEC_ANGLE(i)) * radius;  
		start.y = center.y + sinf(MINSEC_ANGLE(i)) * radius;  

		Vector2 end;
		end.x = center.x + cosf(MINSEC_ANGLE(i)) * RADIUS;  
		end.y = center.y + sinf(MINSEC_ANGLE(i)) * RADIUS; 

		DrawLineEx(start, end, MARKS_THICK, GRAY);
	}
}

void DrawSecHand(Vector2 center, Vector2 *last, i32 t) {
	Vector2 end;
	end.x = center.x + cosf(MINSEC_ANGLE(t) - 90.0f*DEG2RAD) * SEC_HAND_LEN; 
	end.y = center.y + sinf(MINSEC_ANGLE(t) - 90.0f*DEG2RAD) * SEC_HAND_LEN; 

	*last = Vector2Lerp(*last, end, 0.2f);

	DrawLineEx(center, *last, SEC_HAND_THICK, RED);
}

void DrawMinHand(Vector2 center, Vector2 *last, i32 t) {
	Vector2 end;
	end.x = center.x + cosf(MINSEC_ANGLE(t) - 90.0f*DEG2RAD) * MIN_HAND_LEN; 
	end.y = center.y + sinf(MINSEC_ANGLE(t) - 90.0f*DEG2RAD) * MIN_HAND_LEN; 

	*last = Vector2Lerp(*last, end, 0.2f);

	DrawLineEx(center, *last, MIN_HAND_THICK, DARKGRAY);
}

void DrawHourHand(Vector2 center, Vector2 *last, i32 t) {
	Vector2 end;
	end.x = center.x + cosf(HOUR_ANGLE(t) - 90.0f*DEG2RAD) * HOUR_HAND_LEN; 
	end.y = center.y + sinf(HOUR_ANGLE(t) - 90.0f*DEG2RAD) * HOUR_HAND_LEN; 

	*last = Vector2Lerp(*last, end, 0.2f);

	DrawLineEx(center, *last, HOUR_HAND_THICK, BLACK);
}

i32 main(void) {
	InitWindow(WIDTH, HEIGHT, "Clock");	
	SetTargetFPS(60);

	Vector2 center = (Vector2) {
		(float) WIDTH  / 2.0f,
		(float) HEIGHT / 2.0f
	};

	Vector2 sec_hand_last = {0};
	Vector2 min_hand_last = {0};
	Vector2 hour_hand_last = {0};

	while (!WindowShouldClose()) {
		time_t now = time(NULL);
		struct tm *t = localtime(&now);

		BeginDrawing();	
			ClearBackground(DARKBLUE);
			DrawCircleV(center, RADIUS, RAYWHITE);	
			DrawClockMarks(center);
			DrawSecHand(center, &sec_hand_last, t->tm_sec);
			DrawMinHand(center, &min_hand_last, t->tm_min);	
			DrawHourHand(center, &hour_hand_last, t->tm_hour);
		EndDrawing();
	}

	CloseWindow();
	return 0;
}
