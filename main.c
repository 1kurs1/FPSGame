#include "vendor/raylib/src/raylib.h"
#include "vendor/raylib/src/raymath.h"

#define WIDTH 1600
#define HEIGHT 900

typedef struct transform{
    Vector3 scale;
    Vector3 rotationAxis;
    float rotationAngle;
    Vector3 position;
} transform_t;

typedef struct weapon{
    Model model;
    Camera camera;

    transform_t transform;
} weapon_t;

Camera loadCamera(Vector3 pos, Vector3 target){
    Camera cam = {0};
    cam.position = pos;
    cam.target = target;
    cam.up = (Vector3){0, 1, 0};
    cam.fovy = 60;
    cam.projection = CAMERA_PERSPECTIVE;

    return cam;
}

void drawFloor(Camera cam){
    BeginMode3D(cam);
    DrawGrid(100, 0.5f);
    EndMode3D();
}

void drawWeapon(weapon_t weapon){
    BeginMode3D(weapon.camera);
    DrawModelEx(weapon.model, weapon.transform.position, weapon.transform.rotationAxis, weapon.transform.rotationAngle, weapon.transform.scale, WHITE);
    EndMode3D();
}

void freeWeapon(weapon_t weapon){
    UnloadModel(weapon.model);
}

int main(){
    InitWindow(GetScreenWidth(), GetScreenHeight(), "Counteract");

    Camera mainCamera = loadCamera((Vector3){0, 2, 4}, (Vector3){0, 2, 3});
    Camera weaponCamera = loadCamera(Vector3Zero(), (Vector3){0, 0, 1});

    weapon_t ak47 = {0};
    ak47.model = LoadModel("assets/ak47.glb");
    ak47.camera = weaponCamera;
    ak47.transform.scale = (Vector3){0.6, 0.6, 0.6};
    ak47.transform.rotationAngle = 90;
    ak47.transform.rotationAxis = (Vector3){1, 0, 0};
    ak47.transform.position = (Vector3){-0.25, -0.3, 0.3};

    while(!WindowShouldClose()){
        HideCursor();

        SetTargetFPS(60);
        UpdateCamera(&mainCamera, CAMERA_FIRST_PERSON);
        
        BeginDrawing();
        ClearBackground((Color){53, 81, 92, 100});

        drawFloor(mainCamera);
        drawWeapon(ak47);

        EndDrawing();
    }

    freeWeapon(ak47);
    CloseWindow();

    return 0;
}