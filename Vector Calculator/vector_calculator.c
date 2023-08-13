#include <stdio.h>

typedef struct vector2
{
  float x;
  float y;
} vec2;

typedef struct vector3
{
  float x;
  float y;
  float z;
} vec3;


void solve2D ();
void solve3D ();

char ask_operation ();

vec2 add2D (vec2, vec2);
vec3 add3D (vec3, vec3);

vec2 subtract2D (vec2, vec2);
vec3 subtract3D (vec3, vec3);

float dot2D (vec2, vec2);
float dot3D (vec3, vec3);

float cross2D (vec2, vec2);
vec3 cross3D (vec3, vec3);


int main ()
{
  int choice;
  do
    {
      printf ("\nEnter 0 for 2D vector and 1 for 3D vector:");
      scanf ("%d", &choice);

      if (choice == 0)
	solve2D ();
      else if (choice == 1)
	solve3D ();

      printf ("\nEnter '1' to continue else '0':");
      scanf ("%d", &choice);

    }
  while (choice == 1);
}

void solve2D ()
{
  vec2 a, b, result;
  int operation;
  float magnitude;

  printf ("\nEnter a 2D vector x and y component:");
  scanf ("%f %f", &a.x, &a.y);

  printf ("\nEnter another 2D vector x and y component:");
  scanf ("%f %f", &b.x, &b.y);

  operation = ask_operation ();

  switch (operation)
    {
    case 1:
      result = add2D (a, b);

      printf ("\nThe sum of the two vectors is (%.2f %.2f)\n", result.x, result.y);
      break;

    case 2:
      result = subtract2D (a, b);

      printf ("\nThe subtraction of the two vectors is (%.2f %.2f)\n", result.x, result.y);
      break;

    case 3:
      magnitude = dot2D (a, b);

      printf ("\nThe dot product of the two vectors is %.2f\n", magnitude);
      break;

    case 4:
      magnitude = cross2D (a, b);

      printf ("\nThe cross product of the two vectors is a vector a vector of magnitude %.2f and direction perpendicular to both vectors\n", magnitude);
      break;

    default:
      printf ("\nInvalid Input!\n");
    }
}

void solve3D ()
{
  vec3 a, b, result;
  int operation;
  float magnitude;

  printf ("\nEnter a 3D vector x and y component:");
  scanf ("%f %f %f", &a.x, &a.y, &a.z);

  printf ("\nEnter another 3D vector x and y component:");
  scanf ("%f %f %f", &b.x, &b.y, &b.z);

  operation = ask_operation ();

  switch (operation)
    {
    case 1:
      result = add3D (a, b);

      printf ("\nThe sum of the two vectors is (%.2f %.2f %.2f)\n", result.x, result.y, result.z);
      break;

    case 2:
      result = subtract3D (a, b);

      printf ("\nThe subtraction of the two vectors is (%.2f %.2f %.2f)\n", result.x, result.y, result.z);
      break;

    case 3:
      magnitude = dot3D (a, b);

      printf ("\nThe dot product of the two vectors is %.2f\n", magnitude);
      break;

    case 4:
      result = cross3D (a, b);

      printf ("\nThe cross product of the two vectors is (%.2f %.2f %.2f)\n", result.x, result.y, result.z);
      break;
      break;

    default:
      printf ("\nInvalid Input!\n");
    }
}


char
ask_operation ()
{
  int operation;

  printf ("\n\nEnter '1' for vector addition");
  printf ("\nEnter '2' for vector subtraction");
  printf ("\nEnter '3' for dot product");
  printf ("\nEnter '4' for cross product");
  printf ("\n\nWhich operation do you want to do?:");

  scanf ("%d", &operation);
  return operation;

}

vec2 add2D (vec2 a, vec2 b)
{

  vec2 sum;
  sum.x = a.x + b.x;
  sum.y = a.x + b.y;

  return sum;
}

vec2 subtract2D (vec2 a, vec2 b)
{

  vec2 diff;
  diff.x = a.x - b.x;
  diff.y = a.x - b.y;

  return diff;
}

float dot2D (vec2 a, vec2 b)
{

  float dot;
  dot = (a.x * b.x) + (a.y * b.y);

  return dot;
}

float cross2D (vec2 a, vec2 b)
{

  float cross;
  cross = (a.x * b.y) - (b.x * a.y);

  return cross;
}


vec3 add3D (vec3 a, vec3 b)
{

  vec3 sum;
  sum.x = a.x + b.x;
  sum.y = a.y + b.y;
  sum.z = a.z + b.z;

  return sum;
}

vec3 subtract3D (vec3 a, vec3 b)
{

  vec3 diff;
  diff.x = a.x - b.x;
  diff.y = a.y - b.y;
  diff.z = a.z - b.z;

  return diff;
}

float dot3D (vec3 a, vec3 b)
{

  float dot;
  dot = (a.x * b.x) + (a.y * b.y) + (a.z * b.z);

  return dot;
}

vec3 cross3D (vec3 a, vec3 b)
{

  vec3 cross;
  cross.x = (a.y * b.z) - (b.y * a.z);
  cross.y = -((a.x * b.z) - (b.x * a.z));
  cross.z = (a.x * b.y) - (b.x * a.y);

  return cross;
}
