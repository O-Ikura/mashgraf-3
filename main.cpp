#include "common.h"
//#include "Player.h"
#include "Enemies.h"
#include <string>
#include <vector>

#define GLFW_DLL
#include <GLFW/glfw3.h>

constexpr GLsizei WINDOW_WIDTH = 40 * tileSize, WINDOW_HEIGHT = 40 * tileSize;
constexpr int NUM_OF_LEVELS = 3;

struct InputState
{
    bool keys[1024]{};                //массив состояний кнопок - нажата/не нажата
    GLfloat lastX = 400, lastY = 300; //исходное положение мыши
    bool firstMouse = true;
    bool captureMouse = true; // Мышка захвачена нашим приложением или нет?
    bool capturedMouseJustNow = false;
} static Input;

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

void OnKeyboardPressed(GLFWwindow *window, int key, int scancode, int action, int mode)
{
    switch (key)
    {
    case GLFW_KEY_ESCAPE:
        if (action == GLFW_PRESS)
            glfwSetWindowShouldClose(window, GL_TRUE);
        break;
    case GLFW_KEY_1:
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        break;
    case GLFW_KEY_2:
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        break;
    default:
        if (action == GLFW_PRESS)
            Input.keys[key] = true;
        else if (action == GLFW_RELEASE)
            Input.keys[key] = false;
    }
}

void processPlayerMovement(Player &player, std::vector<std::vector<char>> &lvl)
{
    if (Input.keys[GLFW_KEY_W])
        player.ProcessInput(MovementDir::UP, lvl);
    else if (Input.keys[GLFW_KEY_S])
        player.ProcessInput(MovementDir::DOWN, lvl);
    if (Input.keys[GLFW_KEY_A])
        player.ProcessInput(MovementDir::LEFT, lvl);
    else if (Input.keys[GLFW_KEY_D])
        player.ProcessInput(MovementDir::RIGHT, lvl);
    if (!Input.keys[GLFW_KEY_W] && !Input.keys[GLFW_KEY_S] && !Input.keys[GLFW_KEY_A] && !Input.keys[GLFW_KEY_D]) {
        player.Patient();
    }
}

void OnMouseButtonClicked(GLFWwindow *window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
        Input.captureMouse = !Input.captureMouse;

    if (Input.captureMouse)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        Input.capturedMouseJustNow = true;
    }
    else
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void OnMouseMove(GLFWwindow *window, double xpos, double ypos)
{
    if (Input.firstMouse)
    {
        Input.lastX = float(xpos);
        Input.lastY = float(ypos);
        Input.firstMouse = false;
    }

    GLfloat xoffset = float(xpos) - Input.lastX;
    GLfloat yoffset = Input.lastY - float(ypos);

    Input.lastX = float(xpos);
    Input.lastY = float(ypos);
}

void OnMouseScroll(GLFWwindow *window, double xoffset, double yoffset)
{
    // ...
}

int initGL()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize OpenGL context" << std::endl;
        return -1;
    }

    std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "Version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

    std::cout << "Controls: " << std::endl;
    std::cout << "press right mouse button to capture/release mouse cursor  " << std::endl;
    std::cout << "W, A, S, D - movement  " << std::endl;
    std::cout << "press ESC to exit" << std::endl;

    return 0;
}

int main(int argc, char **argv)
{
    if (!glfwInit())
        return -1;

    //	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    //	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow *window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "task1 base project", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, OnKeyboardPressed);
    glfwSetCursorPosCallback(window, OnMouseMove);
    glfwSetMouseButtonCallback(window, OnMouseButtonClicked);
    glfwSetScrollCallback(window, OnMouseScroll);

    if (initGL() != 0)
        return -1;

    //Reset any OpenGL errors which could be present for some reason
    GLenum gl_error = glGetError();
    while (gl_error != GL_NO_ERROR)
        gl_error = glGetError();

    std::vector<std::string> tiles(NUM_OF_TILES);
    tiles[Tile::WALL] = std::string("../resources/tile001.png");
    tiles[Tile::FLOOR] = std::string("../resources/tile024.png");
    tiles[Tile::TRAP] = std::string("../resources/tile034.png");
    tiles[Tile::FINISH] = std::string("../resources/finish.png");
    Level level(tiles);
    std::vector<std::string> levels( {
            "../resources/level1.txt",
            "../resources/level2.txt",
            "../resources/level3.txt",
            } );
    int cur_level = 0;
    level.ReadFromFile(levels[cur_level]);
    level.Draw();

    Point starting_pos{level.GetStartPos()};
    Point finish_pos{level.GetFinishPos()};

    std::vector<Enemy*> enemies;
    
    //Инициализация врагов
    auto &tmp = level.GetInfo();
    for (int y = 0; y < MAP_SIZE; ++y) {
        for (int x = 0; x < MAP_SIZE; ++x) {
            switch (tmp[x][y])
            {
            case 'T':
                enemies.push_back(new Trap({.x = x * tileSize, .y = y * tileSize}));
            
            default:
                break;
            }
        }
    }

    Player player(starting_pos);

    Image screenBuffer(WINDOW_WIDTH, WINDOW_HEIGHT, 4);
    //Image background(WINDOW_WIDTH, WINDOW_HEIGHT, 4);


    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT); GL_CHECK_ERRORS;
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); GL_CHECK_ERRORS;

    //game loop
    while (!glfwWindowShouldClose(window))
    {
        level.GetImage().Draw(0, 0, screenBuffer);
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glfwPollEvents();
        if (!player.IsDead()) {
            processPlayerMovement(player, level.GetMap());

            for (auto i: enemies) {
                i->Update(player);
            }
        }

        Point tmp = player.GetCoords();
        //std::cout << tmp.x << ' ' << tmp.y << ' ' << finish_pos.x << ' ' << finish_pos.y << '\n';
        if ((finish_pos.x <= tmp.x) &&
            (tmp.x <= finish_pos.x + tileSize) &&
            (finish_pos.y <= tmp.y) &&
            (tmp.y <= finish_pos.y + tileSize)) 
        {
            //std::cout << "i came\n";
            cur_level++;
            if (cur_level < NUM_OF_LEVELS) {
                level.ReadFromFile(levels[cur_level]);
                level.Draw();
                player.SetCoords(level.GetStartPos());
            }
            else {
                Image win_msg("../resources/win_msg.png");
                win_msg.Draw( (WINDOW_WIDTH - win_msg.Width())/2, (WINDOW_HEIGHT - win_msg.Height())/2, screenBuffer);
            }
            
        }

        for (auto i: enemies) {
            i->Draw(screenBuffer);
        }
        player.Draw(screenBuffer);

        if (player.IsDead()) {
            Image death_msg("../resources/death_msg.png");
            death_msg.Draw( (WINDOW_WIDTH - death_msg.Width())/2, (WINDOW_HEIGHT - death_msg.Height())/2, screenBuffer);
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); GL_CHECK_ERRORS;
        glDrawPixels(WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGBA, GL_UNSIGNED_BYTE, screenBuffer.Data()); GL_CHECK_ERRORS;

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}
