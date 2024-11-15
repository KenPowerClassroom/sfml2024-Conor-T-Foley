#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

int minesweeper()
{
    //Sets the seed for random number generation
    srand(time(0));

    RenderWindow app(VideoMode(400, 400), "Minesweeper!");

    //This is a magic number that seems to be responsilbe for the squares on the grid being 32x32?
    const int WIDTH_AND_HEIGHT_OF_TILES=32;

    //Non descriptive names
    int underlyingGrid[12][12]; //Only 10x10 of the 12x12 grid is being drawn, this is the underlying grid
    int shownToPlayerGrid[12][12]; //This is the grid shown to the player while the game runs

    Texture tileTexture; //There are many letters in this code, this doesnt need to be another one
    tileTexture.loadFromFile("images/minesweeper/tiles.jpg");
    Sprite tileSprite(tileTexture); //Rename with a better name


    //This loop is randomly allocating where the mines go
    //Each square has a 1 in 5 chnce to get a mine
    //The number 9 repsesents the mines
    for (int i=1;i<=10;i++)
     for (int j=1;j<=10;j++)
      {
        shownToPlayerGrid[i][j]=10;
        if (rand()%5==0)  underlyingGrid[i][j]=9;
        else underlyingGrid[i][j]=0;
      }


    //This loop is going through each tile on the grid
    //Checking if that tile is a mine
    //Then checking how many surrounding square have mines and keeping a count
    for (int i=1;i<=10;i++)
     for (int j=1;j<=10;j++)
      {
        int n=0;
        if (underlyingGrid[i][j]==9) continue;
        if (underlyingGrid[i+1][j]==9) n++;
        if (underlyingGrid[i][j+1]==9) n++;
        if (underlyingGrid[i-1][j]==9) n++;
        if (underlyingGrid[i][j-1]==9) n++;
        if (underlyingGrid[i+1][j+1]==9) n++;
        if (underlyingGrid[i-1][j-1]==9) n++;
        if (underlyingGrid[i-1][j+1]==9) n++;
        if (underlyingGrid[i+1][j-1]==9) n++;
        underlyingGrid[i][j]=n;
      }

    while (app.isOpen())
    {
        Vector2i mousePosition = Mouse::getPosition(app);
        //These keep a track of which square the mouse is in 
        int x = mousePosition.x/ WIDTH_AND_HEIGHT_OF_TILES;
        int y = mousePosition.y/ WIDTH_AND_HEIGHT_OF_TILES;

        Event event; 

        //As long as the program is listening for events....
        while (app.pollEvent(event))
        {
            //If that event is clicking the X, close the app
            if (event.type == Event::Closed)
                app.close();
            //If the event is a mouse click..
            if (event.type == Event::MouseButtonPressed)
                //If the event is a left click reveal the square the mouse is in 
              if (event.key.code == Mouse::Left) shownToPlayerGrid[x][y]= underlyingGrid[x][y];
                //Else if the mouse click is a right click, place a flag
              else if (event.key.code == Mouse::Right) shownToPlayerGrid[x][y]=11;
        }
        //Clears the screen before drawing the game
        app.clear(Color::White);

        //Iterates through each tile in the grid
        for (int i=1;i<=10;i++)
         for (int j=1;j<=10;j++)
          {
             //If that tile has a mine on it reveal the whole board?
           if (shownToPlayerGrid[x][y]==9) shownToPlayerGrid[i][j]= underlyingGrid[i][j];
           //Sets each tile to have the correct texture from the spritesheet, mine blank number etc..
           tileSprite.setTextureRect(IntRect(shownToPlayerGrid[i][j]* WIDTH_AND_HEIGHT_OF_TILES,0, WIDTH_AND_HEIGHT_OF_TILES, WIDTH_AND_HEIGHT_OF_TILES));
           //Places the sprites on the correct parts of the grid
           tileSprite.setPosition(i* WIDTH_AND_HEIGHT_OF_TILES, j* WIDTH_AND_HEIGHT_OF_TILES);
           app.draw(tileSprite);
          }

        app.display();
    }

    return 0;
}
