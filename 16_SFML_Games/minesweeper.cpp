#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

int minesweeper()
{
    srand(time(0));

    RenderWindow app(VideoMode(400, 400), "Minesweeper!");

    //This is a magic number that seems to be responsilbe for the squares on the grid being 32x32?
    int w=32;

    //Non descriptive names
    int grid[12][12]; //Only 10x10 of the 12x12 grid is being drawn, this is the underlying grid
    int sgrid[12][12]; //This is the grid shown to the player while the game runs

    Texture t; //There are many letters in this code, this doesnt need to be another one
    t.loadFromFile("images/minesweeper/tiles.jpg");
    Sprite s(t); //Rename with a better name


    //This loop is randomly allocating where the mines go
    //Each square has a 1 in 5 chnce to get a mine
    //The number 9 repsesents the mines
    for (int i=1;i<=10;i++)
     for (int j=1;j<=10;j++)
      {
        sgrid[i][j]=10;
        if (rand()%5==0)  grid[i][j]=9;
        else grid[i][j]=0;
      }


    //This loop is going through each tile on the grid
    //Checking if that tile is a mine
    //Then checking how many surrounding square have mines and keeping a count
    for (int i=1;i<=10;i++)
     for (int j=1;j<=10;j++)
      {
        int n=0;
        if (grid[i][j]==9) continue;
        if (grid[i+1][j]==9) n++;
        if (grid[i][j+1]==9) n++;
        if (grid[i-1][j]==9) n++;
        if (grid[i][j-1]==9) n++;
        if (grid[i+1][j+1]==9) n++;
        if (grid[i-1][j-1]==9) n++;
        if (grid[i-1][j+1]==9) n++;
        if (grid[i+1][j-1]==9) n++;
        grid[i][j]=n;
      }

    while (app.isOpen())
    {
        Vector2i pos = Mouse::getPosition(app);
        //These keep a track of which square the mouse is in 
        int x = pos.x/w;
        int y = pos.y/w;

        Event e;

        //As long as the program is listening for events....
        while (app.pollEvent(e))
        {
            //If that event is clicking the X, close the app
            if (e.type == Event::Closed)
                app.close();
            //If the event is a mouse click..
            if (e.type == Event::MouseButtonPressed)
                //If the event is a left click reveal the square the mouse is in 
              if (e.key.code == Mouse::Left) sgrid[x][y]=grid[x][y];
                //Else if the mouse click is a right click, place a flag
              else if (e.key.code == Mouse::Right) sgrid[x][y]=11;
        }
        //Clears the screen before drawing the game
        app.clear(Color::White);

        //Iterates through each tile in the grid
        for (int i=1;i<=10;i++)
         for (int j=1;j<=10;j++)
          {
             //If that tile has a mine on it reveal the whole board?
           if (sgrid[x][y]==9) sgrid[i][j]=grid[i][j];
           //Sets each tile to have the correct texture from the spritesheet, mine blank number etc..
           s.setTextureRect(IntRect(sgrid[i][j]*w,0,w,w));
           //Places the sprites on the correct parts of the grid
           s.setPosition(i*w, j*w);
           app.draw(s);
          }

        app.display();
    }

    return 0;
}
