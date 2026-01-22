#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <iostream>
int screenW = 1024;
int screenH = 640;
const int mapSizeY = 16;
const int mapSizeX = 16;
float playerX = 1.5f;
float playerY = 1.5f;
float speed = 0.05f;
float cameraspeed = 0.03f;
float playerAngle = 0.05f;
float luchX;
float luchY;
float kydaLuchX;
float kydaLuchY;
float startX;
float startY;

int map[mapSizeY][mapSizeX] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,1,2,3,4,4,3,2,1,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}


};

float wallfound(float startX, float startY, float ugol, int& wallType, int& side, float& wallHitX) {
    int side1 = 0; // 0 - vertikal 1 - gorizontal
    int stepX = 0;
    int stepY = 0;
    float shagPoX;
    float shagPoY;
    int tekushX = (int)startX;
    int tekushY = (int)startY;
    kydaLuchX = cos(ugol);
    kydaLuchY = sin(ugol);
    shagPoX = fabsf(1.0f / kydaLuchX);
    shagPoY = fabsf(1.0f / kydaLuchY);
    float distance;

    

    if (kydaLuchX < 0) {
        stepX = -1;
        kydaLuchX = (startX - tekushX)  * shagPoX;
    } else {
        stepX = 1;
        kydaLuchX = (tekushX + 1.0f - startX)  * shagPoX;
    }

    if (kydaLuchY < 0) {
        stepY = -1;
        kydaLuchY = (startY - tekushY)  * shagPoY;
    } else {
        stepY = 1;
        kydaLuchY = (tekushY + 1.0f - startY)  * shagPoY;
    }
    bool naidenaStena = false;

    while (naidenaStena == false) {
        
        if (kydaLuchX < kydaLuchY) {
            kydaLuchX += shagPoX;
            tekushX += stepX;
            side = 0;
        } else {
            kydaLuchY += shagPoY;
            tekushY += stepY;
            side = 1;
        }

        if (map[tekushY][tekushX] > 0) {
            naidenaStena = true;
}
    
    }
    if (side == 0) {
        
        distance = (tekushX - startX + (1 - stepX) / 2.0f) / cos(ugol);
        if (distance < 0.1f) distance = 0.1f;
        wallHitX = startY + distance * sin(ugol);
    } else {
        
        distance = (tekushY - startY + (1 - stepY) / 2.0f) / sin(ugol);
        if (distance < 0.1f) distance = 0.1f;
        wallHitX = startX + distance * cos(ugol);
}   
    
    wallHitX -= floor(wallHitX);
    wallType = map[tekushY][tekushX];
    side1 = side;
    return distance;
        
}



void raycast(sf::RenderWindow& window) {
    sf::Texture wallTexture[5];
    wallTexture[1].loadFromFile("textures/stone_brick1.png");
    wallTexture[2].loadFromFile("textures/stone_gray1.png");
    wallTexture[3].loadFromFile("textures/wall_vines1.png");
    wallTexture[4].loadFromFile("textures/cobble_blood2.png");



    int textureWidth = wallTexture[1].getSize().x;   
    int textureHeight = wallTexture[1].getSize().y;  

    int textureWidth2 = wallTexture[2].getSize().x;   
    int textureHeight2 = wallTexture[2].getSize().y;  

    int textureWidth3 = wallTexture[3].getSize().x;   
    int textureHeight3 = wallTexture[3].getSize().y;

    int textureWidth4 = wallTexture[4].getSize().x;   
    int textureHeight4 = wallTexture[4].getSize().y;   


    sf::RectangleShape ground(sf::Vector2f(screenW, screenH / 2));
    ground.setPosition(0,screenH / 2);
    ground.setFillColor(sf::Color(192,190,192));
    window.draw(ground);


 

    sf::RectangleShape sky(sf::Vector2f(screenW, screenH / 2));
    sky.setPosition(0,0);
    sky.setFillColor(sf::Color(28, 170, 214));
    window.draw(sky);



    int wallType, side;
    sf::Color color;
    int stepX, stepY;

    // для разных типов стен
    sf::VertexArray wallType1(sf::Quads);
    sf::VertexArray wallType2(sf::Quads);
    sf::VertexArray wallType3(sf::Quads);
    sf::VertexArray wallType4(sf::Quads);
/*
    wallType1.clear();
    wallType2.clear();
    wallType3.clear(); 

    wallType1.resize(screenW * 4);  
    wallType2.resize(screenW * 4);
    wallType3.resize(screenW * 4);
*/


    // цикл рэйкаста
    for(int luch = 0; luch < screenW; luch++) {
        float cameraX = 2.0f * luch / screenW - 1.0f;   
        float kydaLuch = playerAngle + cameraX * 0.5f;
        float wallHitX;
        float distance = wallfound(playerX, playerY, kydaLuch, wallType, side, wallHitX);

         // float visota = screenH / distance;
        // drawVerticalLine(window, luch, visota, wallType, side, stepX, stepY);
        if (luch == screenW/2) { 
            static float lastWallHitX = 0;
            float diff = wallHitX - lastWallHitX;

            lastWallHitX = wallHitX;

}
        int currentTexWidth, currentTexHeight;


        // для  текстур
        if (wallType == 1) {
            currentTexWidth = textureWidth;
            currentTexHeight = textureHeight;
    }   else if (wallType == 2) {
            currentTexWidth = textureWidth2;
            currentTexHeight = textureHeight2;
}
        else if (wallType == 3) {
            currentTexWidth = textureWidth3;
            currentTexHeight = textureHeight3;
}
        else if (wallType == 4) {
            currentTexWidth = textureWidth4;
            currentTexHeight = textureHeight4;
}
        
        int textureX = (int)(wallHitX * currentTexWidth); 

                if (textureX < 0) textureX = 0;
                if (textureX >= currentTexWidth) textureX = currentTexWidth - 1;

                float angleDiff = kydaLuch - playerAngle;
                float cosDiff = cos(angleDiff);
                if (fabs(cosDiff) < 0.001f) cosDiff = 0.001f; // защита от нуля
               
               
            
                float lineHeight = screenH / distance;
                float maxHeight = screenW;
                float drawStart = screenH / 2.0f - lineHeight / 2.0f; 
                float drawEnd = screenH / 2.0f + lineHeight / 2.0f;  
                
            
                


                float texU = wallHitX * currentTexWidth;
                // if (texU < 1.0f) texU = 1.0f;  
                // if (texU > textureWidth - 2.0f) texU = textureWidth - 2.0f;  
                sf::Vertex v0, v1, v2, v3;  
            
                v0.position = sf::Vector2f(luch, drawStart);
                v1.position = sf::Vector2f(luch + 1, drawStart);
                v2.position = sf::Vector2f(luch + 1, drawEnd);
                v3.position = sf::Vector2f(luch, drawEnd);
    
                float texTop = 0;
                float texBottom = currentTexHeight;
/*
                if (lineHeight > screenH) {
                    float scale = screenH / lineHeight; // scale - доля/часть текстуры которую видно на экране
                    texTop = textureHeight * (1.0f - scale) / 2.0f; //textop - верхняя часть текстуры,textureHeight - высота текстуры
                    texBottom = textureHeight - texTop; //  texBottom - нижнняя часть текстуры
                }
*/
                v0.texCoords = sf::Vector2f(texU, texTop);
                v1.texCoords = sf::Vector2f(texU + 1.0f, texTop);
                v2.texCoords = sf::Vector2f(texU + 1.0f, texBottom);
                v3.texCoords = sf::Vector2f(texU, texBottom);
 
                if (wallType == 1) {
                    wallType1.append(v0);
                    wallType1.append(v1);
                    wallType1.append(v2);
                    wallType1.append(v3);
                }   else if (wallType == 2) {
                    wallType2.append(v0);
                    wallType2.append(v1);
                    wallType2.append(v2);
                    wallType2.append(v3);
                }   
                    else if (wallType == 3) {
                    wallType3.append(v0);
                    wallType3.append(v1);
                    wallType3.append(v2);
                    wallType3.append(v3);
                }

                                  
                    else if (wallType == 4) {
                    wallType4.append(v0);
                    wallType4.append(v1);
                    wallType4.append(v2);
                    wallType4.append(v3);
                }






            
              
            
  
    

 

                

            }   
            
            window.draw(wallType1, &wallTexture[1]);
            window.draw(wallType2, &wallTexture[2]);
            window.draw(wallType3, &wallTexture[3]);
            window.draw(wallType4, &wallTexture[4]);
        
            

    }
  




int main()
{
    sf::RenderWindow window(sf::VideoMode(screenW, screenH), "3D-Game");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        int tekushX;
        int tekushY;

        window.setFramerateLimit(40);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
            speed = 0.09f;
        } else {
            speed = 0.05f;
        }


        float moveX = 0;
        float moveY = 0;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {

            float colisionColide = 0.5f;

            float colisionX  = playerX + cos(playerAngle) * speed;
            float colisionY  = playerY + sin(playerAngle) * speed;

            float checkX = colisionX + cos(playerAngle) * colisionColide;
            int cellX = (int)checkX;
            int cellY = (int)playerY;
    
            if (map[cellY][cellX] == 0) {
                playerX = colisionX; 
    }
    
            float checkY = colisionY + sin(playerAngle) * colisionColide;
            cellX = (int)playerX; 
            cellY = (int)checkY;
    
            if (map[cellY][cellX] == 0) {
                playerY = colisionY; 
    }
}
     
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {

            float colisionColide = 0.5f;

            float colisionX  = playerX - cos(playerAngle) * speed;
            float colisionY  = playerY - sin(playerAngle) * speed;

            float checkX = colisionX - cos(playerAngle) * colisionColide;
            int cellX = (int)checkX;
            int cellY = (int)playerY;
    
            if (map[cellY][cellX] == 0) {
                playerX = colisionX; 
    }
    
            float checkY = colisionY - sin(playerAngle) * colisionColide;
            cellX = (int)playerX; 
            cellY = (int)checkY;
    
            if (map[cellY][cellX] == 0) {
                playerY = colisionY; 
    } 
}  

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {



            
            float colisionColide = 0.2f;

            float colisionX  = playerX + sin(playerAngle) * speed;
            float colisionY  = playerY + -cos(playerAngle) * speed;

            float checkX = colisionX + sin(playerAngle) * colisionColide;
            int cellX = (int)checkX;
            int cellY = (int)playerY;
    
            if (map[cellY][cellX] == 0) {
                playerX = colisionX; 
    }
    
            float checkY = colisionY + -cos(playerAngle) * colisionColide;
            cellX = (int)playerX; 
            cellY = (int)checkY;
    
            if (map[cellY][cellX] == 0) {
                playerY = colisionY; 
    } 
} 

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            
            float colisionColide = 0.2f;

            float colisionX  = playerX + -sin(playerAngle) * speed;
            float colisionY  = playerY + cos(playerAngle) * speed;

            float checkX = colisionX + -sin(playerAngle) * colisionColide;
            int cellX = (int)checkX;
            int cellY = (int)playerY;
    
            if (map[cellY][cellX] == 0) {
                playerX = colisionX; 
    }
    
            float checkY = colisionY + cos(playerAngle) * colisionColide;
            cellX = (int)playerX; 
            cellY = (int)checkY;
    
            if (map[cellY][cellX] == 0) {
                playerY = colisionY; 
    } 
} 
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
            playerAngle -= cameraspeed;
}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
            playerAngle += cameraspeed;
}

    




        window.clear();
        sf::Color color (255, 255, 255);
        raycast(window);







        window.display();
    }

    return 0;
}






