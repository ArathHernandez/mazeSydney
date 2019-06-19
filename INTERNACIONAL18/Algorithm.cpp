#include <Arduino.h>
#include "Algorithm.h"

Algorithm::Algorithm(){}

bool v = true;

void Algorithm::clear(byte ox, byte oy)
{
  pointers auxValor;
  auxValor.px = -1;
  auxValor.py = -1;
  objX = ox;
  objY = oy;

  for(byte i = 0; i < 15; i++)
    {
      for(byte j = 0; j < 15; j++)
        {
          m4p[i][j] = -1;
          save[i][j] = auxValor;
          algorithmVisiteds[i][j] = false;
        }
    }

  for(byte i = 0; i < 100; i++)
    {
      moves[i] = 'z';
    }

  for(byte i = 0; i <15; i++)
  {
    for(byte j = 0; j < 15; j++)
    {
        if(robot.tile[i][j][robot.z].visited() && !robot.tile[i][j][robot.z].blackTile())
            m4p[i][j] = 0;
        if(robot.tile[i][j][robot.z].visited() && !robot.tile[i][j][robot.z].blackTile() && robot.tile[i][j][robot.z].bumper())
            m4p[i][j] = -2;
    }
  }

  m4p[objX][objY] = 99;
  m4p[robot.x][robot.y] = 0;

  /*for(byte i=0; i<15; i++){
    for(byte j=0;j<15;j++){
      if(m4p[i][j] == -1)
        {
          Serial.print("#");
        }
        else{
      Serial.print(m4p[i][j]);}
      Serial.print("      ");
    }
    Serial.println("");
  }
  Serial.println(" ");*/
}

void Algorithm::startBfs()
{
  QueueArray <costs> sons;
  costs firstCost, secondCost;
  firstCost.node = 0;
  firstCost.a = robot.x;
  firstCost.b = robot.y;
  algorithmVisiteds[robot.x][robot.y] = true;
  sons.push(firstCost);

  while(!sons.isEmpty())
    {
      firstCost = sons.front();
      sons.pop();
      algorithmVisiteds[firstCost.a][firstCost.b] = true;

      if(!algorithmVisiteds[firstCost.a][firstCost.b+1] && m4p[firstCost.a][firstCost.b+1] != -1 && m4p[firstCost.a][firstCost.b+1] != 99 && firstCost.a >= 0 && firstCost.a < 15 && firstCost.b+1 >= 0 && firstCost.b+1 < 15 && !robot.tile[firstCost.a][firstCost.b][robot.z].right())
        {
          if(m4p[firstCost.a-1][firstCost.b] == -2){
            m4p[firstCost.a-1][firstCost.b] = firstCost.node + 10;
            secondCost.node = firstCost.node + 10;
          }else{
            m4p[firstCost.a-1][firstCost.b] = firstCost.node + 1;
            secondCost.node = firstCost.node + 1;
          }
          
          secondCost.a = firstCost.a;
          secondCost.b = firstCost.b+1;
          save[firstCost.a][firstCost.b+1] = {firstCost.a, firstCost.b};
          sons.push(secondCost);
        }

      if(!algorithmVisiteds[firstCost.a][firstCost.b-1] && m4p[firstCost.a][firstCost.b-1] != -1 && m4p[firstCost.a][firstCost.b-1] != 99 && firstCost.a >= 0 && firstCost.a < 15 && firstCost.b-1 >= 0 && firstCost.b-1 < 15 && !robot.tile[firstCost.a][firstCost.b][robot.z].left())
        {
          if(m4p[firstCost.a-1][firstCost.b] == -2){
            m4p[firstCost.a-1][firstCost.b] = firstCost.node + 10;
            secondCost.node = firstCost.node + 10;
          }else{
            m4p[firstCost.a-1][firstCost.b] = firstCost.node + 1;
            secondCost.node = firstCost.node + 1;
          }
          
          secondCost.a = firstCost.a;
          secondCost.b = firstCost.b-1;
          save[firstCost.a][firstCost.b-1] = {firstCost.a,firstCost.b};
          sons.push(secondCost);
        }

      if(!algorithmVisiteds[firstCost.a+1][firstCost.b] && m4p[firstCost.a+1][firstCost.b] != -1 && m4p[firstCost.a+1][firstCost.b] != 99 && firstCost.a+1 >= 0 && firstCost.a+1 < 15 && firstCost.b >= 0 && firstCost.b < 15 && !robot.tile[firstCost.a][firstCost.b][robot.z].down())
        {
          if(m4p[firstCost.a-1][firstCost.b] == -2){
            m4p[firstCost.a-1][firstCost.b] = firstCost.node + 10;
            secondCost.node = firstCost.node + 10;
          }else{
            m4p[firstCost.a-1][firstCost.b] = firstCost.node + 1;
            secondCost.node = firstCost.node + 1;
          }
          
          secondCost.a = firstCost.a+1;
          secondCost.b = firstCost.b;
          save[firstCost.a+1][firstCost.b] = {firstCost.a,firstCost.b};
          sons.push(secondCost);
        }

      if(!algorithmVisiteds[firstCost.a-1][firstCost.b] && m4p[firstCost.a-1][firstCost.b] != -1 && m4p[firstCost.a-1][firstCost.b] != 99 && firstCost.a-1 >= 0 && firstCost.a-1 < 15 && firstCost.b >= 0 && firstCost.b < 15  && !robot.tile[firstCost.a][firstCost.b][robot.z].up())
        {
          if(m4p[firstCost.a-1][firstCost.b] == -2){
            m4p[firstCost.a-1][firstCost.b] = firstCost.node + 10;
            secondCost.node = firstCost.node + 10;
          }else{
            m4p[firstCost.a-1][firstCost.b] = firstCost.node + 1;
            secondCost.node = firstCost.node + 1;
          }

          secondCost.a = firstCost.a-1;
          secondCost.b = firstCost.b;
          save[firstCost.a-1][firstCost.b] = {firstCost.a,firstCost.b};
          sons.push(secondCost);
        }
    }

   /* for(byte i=0; i<15; i++){
    for(byte j=0;j<15;j++){
      if(m4p[i][j] == -1)
        {
          Serial.print("#");
        }
        else{
      Serial.print(m4p[i][j]);}
      Serial.print("      ");
    }
    Serial.println("");
  }
  Serial.println(" ");*/
}

void Algorithm::findWay()
{
  contador = 0;
  menor = 100;
  BFSx = objX;
  BFSy = objY;

  while(m4p[BFSx][BFSy] != 0)
    {
      if((m4p[BFSx][BFSy+1] < menor) && (m4p[BFSx][BFSy+1] != -1) && (algorithmVisiteds[BFSx][BFSy+1] == true) && BFSx >= 0 && BFSy+1 >= 0 && BFSx < 15 && BFSy+1 < 15 && (!robot.tile[BFSx][BFSy][robot.z].right()))
        {
          menor = m4p[BFSx][BFSy+1];
          moves[contador] = 'i';
        }
        
      if((m4p[BFSx+1][BFSy] < menor) && (m4p[BFSx+1][BFSy] != -1) && (algorithmVisiteds[BFSx+1][BFSy] == true) && BFSx+1 >= 0 && BFSy >= 0 && BFSx+1 < 15 && BFSy < 15 && (!robot.tile[BFSx][BFSy][robot.z].down()))
       {
          menor = m4p[BFSx+1][BFSy];
          moves[contador] = 'f';
        }
        
      if((m4p[BFSx-1][BFSy] < menor) && (m4p[BFSx-1][BFSy] != -1) && (algorithmVisiteds[BFSx-1][BFSy] == true) && BFSx-1 >= 0 && BFSy >= 0 && BFSx-1 < 15 && BFSy < 15 && (!robot.tile[BFSx][BFSy][robot.z].up()))
        {
          menor = m4p[BFSx-1][BFSy];
          moves[contador] = 'a';
        }

      if((m4p[BFSx][BFSy-1] < menor) && (m4p[BFSx][BFSy-1] != -1) && (algorithmVisiteds[BFSx][BFSy-1] == true) && BFSx >= 0 && BFSy-1 >= 0 && BFSx < 15 && BFSy-1 < 15 && (!robot.tile[BFSx][BFSy][robot.z].left()))
        {
          menor = m4p[BFSx][BFSy-1];
          moves[contador] = 'd';
        }

      if(moves[contador] == 'i')
        {
          BFSy++;
        }
        else if(moves[contador] == 'f')
          {
            BFSx++;
          }
          else if(moves[contador] == 'a')
            {
              BFSx--;
            }
            else if(moves[contador] == 'd')
              {
                BFSy--;
              }

     //Serial.println(moves[contador]);

     contador++;
    }

    char movesOf[contador];

    for(byte i = 0, j = contador - 1; i < contador; i++, j--)
      {
        movesOf[i] = moves[j];
      }

    for(byte i = 0; i < contador; i++)
      {
        if(i == contador - 1)
        {
          if(movesOf[i] == 'a')
          {
            switch(robot.getDirection())
              {
                case 'N':
                {
                  this -> rightTurn();
                  this -> rightTurn();
                } break;
                case 'E':
                {
                  this -> rightTurn();
                } break;
                case 'W':
                {
                  this -> leftTurn();
                } break;
                case 'S':
                {
                } break;
              }
          }
          else if(movesOf[i] == 'd')
            {
              switch(robot.getDirection())
              {
                case 'N':
                {
                  this -> rightTurn();
                } break;
                case 'E':
                {
                } break;
                case 'W':
                {
                  this -> rightTurn();
                  this -> rightTurn();
                } break;
                case 'S':
                {
                  this -> leftTurn();
                } break;
              }
            }
            else if(movesOf[i] == 'i')
              {
                switch(robot.getDirection())
                  {
                    case 'N':
                    {
                      this -> leftTurn();
                    } break;
                    case 'E':
                    {
                      this -> rightTurn();
                      this -> rightTurn();
                    } break;
                    case 'W':
                    {
                    } break;
                    case 'S':
                    {
                      this -> rightTurn();
                    } break;
                  }
              }
              else if(movesOf[i] == 'f')
                {
                  switch(robot.getDirection())
                    {
                      case 'N':
                      {
                      } break;
                      case 'E':
                      {
                        this -> leftTurn();
                      } break;
                      case 'W':
                      {
                        this -> rightTurn();
                      } break;
                      case 'S':
                      {
                        this -> rightTurn();
                        this -> rightTurn();
                      } break;
                    }
                }
        }
        else
        {
          if(movesOf[i] == 'a')
            {
              switch(robot.getDirection())
                {
                  case 'N':
                  {
                    this -> rightTurn();
                    this -> rightTurn();
                    this -> moveForward(v);
                  } break;
                  case 'E':
                  {
                    this -> rightTurn();
                    this -> moveForward(v);
                  } break;
                  case 'W':
                  {
                    this -> leftTurn();
                    this -> moveForward(v);
                  } break;
                  case 'S':
                  {
                    this -> moveForward(v);
                  } break;
                }
            }
            else if(movesOf[i] == 'd')
              {
                switch(robot.getDirection())
                {
                  case 'N':
                  {
                    this -> rightTurn();
                    this -> moveForward(v);
                  } break;
                  case 'E':
                  {
                    this -> moveForward(v);
                  } break;
                  case 'W':
                  {
                    this -> rightTurn();
                    this -> rightTurn();
                    this -> moveForward(v);
                  } break;
                  case 'S':
                  {
                    this -> leftTurn();
                    this -> moveForward(v);
                  } break;
                }
              }
              else if(movesOf[i] == 'i')
                {
                  switch(robot.getDirection())
                    {
                      case 'N':
                      {
                        this -> leftTurn();
                        this -> moveForward(v);
                      } break;
                      case 'E':
                      {
                        this -> rightTurn();
                        this -> rightTurn();
                        this -> moveForward(v);
                      } break;
                      case 'W':
                      {
                        this -> moveForward(v);
                      } break;
                      case 'S':
                      {
                        this -> rightTurn();
                        this -> moveForward(v);
                      } break;
                    }
                }
                else if(movesOf[i] == 'f')
                  {
                    switch(robot.getDirection())
                      {
                        case 'N':
                        {
                          this -> moveForward(v);
                        } break;
                        case 'E':
                        {
                          this -> leftTurn();
                          this -> moveForward(v);
                        } break;
                        case 'W':
                        {
                          this -> rightTurn();
                          this -> moveForward(v);
                        } break;
                        case 'S':
                        {
                          this -> rightTurn();
                          this -> rightTurn();
                          this -> moveForward(v);
                        } break;
                      }
                  }
      }
  }
}

void Algorithm::moveForward(bool &perfect)
{  
  
  sensors.motors.rightCount = 0;
   int bb = 0;
   uint8_t maxTam = 0;
   int crash = 0;
   uint8_t tam = 0 ;
   int newTic = sensors.motors.tic1;
   sensors.motors.bT=false;
   sensors.motors.bumperControl=false;
   bool fT = true;
   int aux;
   double diE = sensors.getDistanceOf(sensors.echo_E, 3);
   double diA = sensors.getDistanceOf(sensors.echo_A, 4);

  if( diE <= 20)
  {
    perfect=false;
    wrongAlg = true;
    return;
  }
  
if(sensors.motors.bumper(tam))
{
  fT=false;
  newTic+=tam*50;
  sensors.motors.bumperControl=true;
  maxTam=tam;
}
  while(sensors.motors.rightCount < newTic)
    {
      sensors.motors.avanzar(sensors.motors.de, sensors.getDistanceOf(sensors.echo_I, 1), sensors.getDistanceOf(sensors.echo_D, 2), bb);

     /* if(sensors.motors.cuadroNegro())
      {
        reverseRightCount = sensors.motors.rightCount;
        sensors.motors.rightCount = 0;

        while(sensors.motors.rightCount < reverseRightCount)
          sensors.motors.atrasPID(sensors.motors.de);

        sensors.motors.rightCount = 1221;
        sensors.motors.detenerse();
        delay(1000);
      }*/

      if(sensors.temperatureCelcius(sensors.mlxLeft) > (sensors.firstTemperature + 10))
      {
        aux=sensors.motors.rightCount;
        sensors.motors.detenerse();
        robot.dispenser.dropOneKitLeft();
        sensors.motors.rightCount=aux;
      }
      if(sensors.temperatureCelcius(sensors.mlxRight) > (sensors.firstTemperature + 10))
      {
        aux=sensors.motors.rightCount;
        sensors.motors.detenerse();
        robot.dispenser.dropOneKitRight();
        sensors.motors.rightCount=aux;
      }

      value = sensors.motors.rampa(sensors.motors.de);

      if(value != 0)
      {
        robot.tile[robot.x][robot.y][robot.z].ramp(1);

        switch(robot.getDirection())
        {
          case 'N': robot.tile[robot.x-1][robot.y][robot.z].visited(1);
          break;
          case 'E': robot.tile[robot.x][robot.y+1][robot.z].visited(1);
          break;
          case 'W': robot.tile[robot.x][robot.y-1][robot.z].visited(1);
          break;
          case 'S': robot.tile[robot.x+1][robot.y][robot.z].visited(1);
          break;
        }

        (value == 1) ? robot.z++ : robot.z--;

        if(robot.z == 4)
          robot.dataTransferUpFloor();
        else if(robot.z == -1)
          robot.dataTransferDownFloor();

        switch(robot.getDirection())
        {
          case 'N': robot.tile[robot.x-1][robot.y][robot.z].ramp(1);
          break;
          case 'E': robot.tile[robot.x][robot.y+1][robot.z].ramp(1);
          break;
          case 'W': robot.tile[robot.x][robot.y-1][robot.z].ramp(1);
          break;
          case 'S': robot.tile[robot.x+1][robot.y][robot.z].ramp(1);
          break;
        }
      }

      if(sensors.motors.rightCount<(newTic * 0.7))
       {
        if(digitalRead(sensors.motors.pin1)==HIGH)
          {
            crash++;
            sensors.motors.choqueDer(sensors.motors.de, 65);
            sensors.motors.rightCount=0;
          }
          if(digitalRead(sensors.motors.pin3)==HIGH)
          {
            crash++;
            sensors.motors.choqueIzq(sensors.motors.de, 65);
            sensors.motors.rightCount=0;
          }
        if(digitalRead(sensors.motors.pin5)==HIGH)
          {
            crash++;
            sensors.motors.choqueIzq(sensors.motors.de, 40);
            sensors.motors.rightCount=0;
          }
        if(digitalRead(sensors.motors.pin4)==HIGH)
          {
            sensors.motors.choqueDer(sensors.motors.de, 40);
            sensors.motors.rightCount=0;
            crash++;
          }
        if(digitalRead(sensors.motors.pin2)==HIGH)
          {
            crash++;
            sensors.motors.choqueDer(sensors.motors.de, 20);
            sensors.motors.rightCount=0;
          }
        if(digitalRead(sensors.motors.pin6)==HIGH)
          {
            crash++;
            sensors.motors.choqueIzq(sensors.motors.de, 20);
            sensors.motors.rightCount=0;
          }
       }

     if(bb>0)
       {
        newTic= newTic + bb*20;
        bb = 0;
        sensors.motors.bT=true;
       }
    

if(!sensors.motors.bumperControl)
{
if(sensors.motors.bumper(tam)){
sensors.motors.bumperControl=true;
maxTam=tam;
}
}
else if(fT)
{
sensors.motors.bumper(tam);

if(tam>=maxTam)
maxTam = tam;
else if (fT){
newTic= newTic+maxTam*50;
fT=false;
}

}


if(crash>3){  //la cagaste
sensors.motors.detenerse();
perfect=false;
return;
}
}
  sensors.motors.detenerse();
  delay(300);
  sensors.motors.checar();

  if(maxTam>=2 && sensors.motors.bumperControl)
  sensors.acomodo(diE,diA);
  
  sensors.checkDistances();
}

void Algorithm::rightTurn()
{
    robot.changeDirection(1, robot.getDirection());

    (sensors.motors.de == 270) ? sensors.motors.de = 0 : sensors.motors.de += 90;
    sensors.motors.giro(sensors.motors.de, sensors.motors.bumperControl);
    sensors.motors.detenerse();
     delay(180);

    sensors.motors.checar();

    //sensors.motors.escribirLetraLCD(robot.getDirection());
    //delay(1000);

    if(sensors.getDistanceOf(sensors.echo_A, 4) <= 21 && !sensors.motors.bumperControl)
      sensors.motors.atrasSN();
    else
      sensors.motors.girosX++;
}

void Algorithm::leftTurn()
{
    robot.changeDirection(3, robot.getDirection());
    (sensors.motors.de == 0) ? sensors.motors.de = 270 : sensors.motors.de -= 90;
    sensors.motors.giro(sensors.motors.de, sensors.motors.bumperControl);
    sensors.motors.detenerse();
    delay(180);

    sensors.motors.checar();

    //sensors.motors.escribirLetraLCD(robot.getDirection());

    if(sensors.getDistanceOf(sensors.echo_A, 4) <= 21 && !sensors.motors.bumperControl)
      sensors.motors.atrasSN();
    else
      sensors.motors.girosX++;
}
