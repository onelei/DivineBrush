#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <FreeImage.h>
#include <iostream>

GLuint loadImageToTexture(const char* filename) {
    FreeImage_Initialise();
    // 图像格式
    FREE_IMAGE_FORMAT format = FreeImage_GetFileType(filename);
    if(format == -1) {
        std::cout << "Could not find image: " << filename << std::endl;
        return 0;
    }

    // 加载图像
    FIBITMAP* bitmap = FreeImage_Load(format, filename);
    if(!bitmap) {
        std::cout << "Failed to load image: " << filename << std::endl;
        return 0;
    }

    // 转换为32位RGB图像
    FIBITMAP* bitmap32 = FreeImage_ConvertTo32Bits(bitmap);
    FreeImage_Unload(bitmap);

    int width = FreeImage_GetWidth(bitmap32);
    int height = FreeImage_GetHeight(bitmap32);

    // 创建纹理
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height,
                 0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(bitmap32));

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    FreeImage_Unload(bitmap32);
    FreeImage_DeInitialise();

    return textureID;
}

int main() {
    GLFWwindow* window;

    if (!glfwInit()) {
        return -1;
    }

    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    const char* imagePath = "../resources/bird.png";
    GLuint textureID = loadImageToTexture(imagePath);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, textureID);

        glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex2f(-1.0f, -1.0f);
        glTexCoord2f(1, 0); glVertex2f( 1.0f, -1.0f);
        glTexCoord2f(1, 1); glVertex2f( 1.0f,  1.0f);
        glTexCoord2f(0, 1); glVertex2f(-1.0f,  1.0f);
        glEnd();

        /*
         * glTexCoord2f         glVertex2f
         * 4(0,1)<---3(1,1)     4(-1,1)<---3(1,1)
         *
         *                             (0,0)
         *
         * 1(0,0)--->2(1,0)     1(-1,-1)--->2(1,-1)
        */

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}