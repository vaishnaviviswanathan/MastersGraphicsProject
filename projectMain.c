/*
 *
 *
 * Default entry of the project will happen in perspective mode without the first person navigation mode - Daylight mode
 *  Key bindings:
 *  arrows     Change view angle in default perspective mode (without first person navigation)
 *  q          First Person Navigation in Perspective
            - Keys
                left arrow  - moves left
                right arrow - moves right
                x - moves in
                v - moves out
 *  r          Rain (on/off) (on/off fog by default)
 *  c          Change to night mode view (Enables lighting as well by default)
 *  w          Snow (on/off)
 *  0          Daylight mode ; Reset view angle and also the entire environment to day time (reset rain, night mode,fog,snow, lighting and fpn mode as well)
 *  m          Default perspective without first person navigation
 *  []         Lower/rise light
 *  a/A        Decrease/increase ambient light
 *  d/D        Decrease/increase diffuse light
 *  s/S        Decrease/increase specular light
 *  e/E        Decrease/increase emitted light
 *  n/N        Decrease/increase shininess
 *  ESC        Exit
 */

#include "CSCIx229.h"
#include "F16.h"
int    fly=0;      //  Animated flight
int    axes=0;     //  Display axes
int    light=1;    //  Lighting
int    F16[3];     //  F16 display list
int    th=90;      //  Azimuth of view angle
int    ph=0;       //  Elevation of view angle
int tree=0;
int fire = 0;

double Yl=2;       //  Elevation of light
double roll=0;     //  Roll angle
double pitch=0;    //  Pitch angle
double yaw=0;      //  Yaw angle
int    pwr=100;    //  Power setting (%)
int    fov=55;     //  Field of view (for perspective)
double asp=1;      //  Aspect ratio
double dim=40.0;  //  Size of world


int entry=1;


int    box=1;    //  Draw sky
int    sky[15];   //  Sky textures

double X  = 0;   //  Location
double Y  = 0;   //  Location
double Z  = 0;   //  Location
double Dx = 1;   //  Direction
double Dy = 0;   //  Direction
double Dz = 0;   //  Direction
double Sx = 1;   //  Sideways
double Sy = 0;   //  Sideways
double Sz = 0;   //  Sideways
double Ux = 1;   //  Up
double Uy = 0;   //  Up
double Uz = 0;   //  Up
double Ox = 0;   //  LookAt
double Oy = 0;   //  LookAt
double Oz = 0;   //  LookAt
double Ex = 1;   //  Eye
double Ey = 1;   //  Eye
double Ez = 1;   //  Eye

int fpn = 0;
int count=0;
int incre=1;


int car1=0;
int car2=0;
int car3=0;

int teeth =0 ;
int coco = 0;
int danger =0;

//int distance  = (int) 3.5*dim*2;    // Light distance

//int distance = 140;
int distance = 0;

// Light values
int one       =   1;    // Unit value
//int distance  = 100;  // Light distance

int inc       =  10;    // Ball increment
int smooth    =   1;    // Smooth/Flat shading
int local     =   0;    // Local Viewer Model
int emission  =   0;    // Emission intensity (%)
int ambient   =  30;    // Ambient intensity (%)
int diffuse   = 100;    // Diffuse intensity (%)
int specular  =   0;    // Specular intensity (%)
int shininess =   0;    // Shininess (power of two)
float shiny   =   1;    // Shininess (value)
int zh        =  90;    // Light azimuth
float ylight  =   0;    // Elevation of light
int move=1;             //  Move light

int nightlight=0;
int nightmode=0;
int rainstart=0;
int snowstart=0;
int building1=0;
int building2=0;
int pyramid=0;
int cylinder1=0,cylinder2=0,cylinder3=0,cylinder4=0;
int city; // building texture
int carmodel=0;
//GLfloat angleCube = 0.0f;     // Rotational angle for cube [NEW]
int increment = 0;
int refreshMills = 400;        // refresh interval in milliseconds [NEW]


//rain
#define MAX_PARTICLES 5000
#define WCX		640
#define WCY		480
#define RAIN	0
#define SNOW	1


float slowdown = 2.0;
float velocity = 0.0;
float zoom = -40.0;
float pan = 0.0;
float tilt = 0.0;

int loop;
int fall;

int fog = 0;

//floor colors
float r = 0.0;
float g = 1.0;
float b = 0.0;
float ground_points[21][21][3];
float ground_colors[21][21][4];
float accum = -10.0;

typedef int bool;
#define true 1
#define false 0

typedef struct
{
    // Life
    bool alive;	// is the particle alive?
    float life;	// particle lifespan
    float fade; // decay
    // color
    float red;
    float green;
    float blue;
    // Position/direction
    float xpos;
    float ypos;
    float zpos;
    // Velocity/Direction, only goes down in y dir
    float vel;
    // Gravity
    float gravity;
}particles;

// Paticle System
particles par_sys[MAX_PARTICLES]; 

// Initialize/Reset Particles - give them their attributes
void initParticles(int i)
{
    if(rainstart==1 || snowstart==1)
    {
    int d = (int) 3.5*dim;
  
    par_sys[i].alive = true;
    par_sys[i].life = 1.0;

    par_sys[i].fade = (float) (rand() % (2*d));
    par_sys[i].xpos = (float) (rand() % (2*d))-d;
    par_sys[i].ypos = 60.0;
    par_sys[i].zpos = (float) (rand() % (2*d))-d;
    
    par_sys[i].red = 0.5;
    par_sys[i].green = 0.5;
    par_sys[i].blue = 1.0;
    
    par_sys[i].vel = velocity;
    par_sys[i].gravity = -0.8;
    }//if ch=='r' else stop raining
}



// For Snow
void drawSnow()
{
    if(snowstart==1)
    {
    double x, y, z;
    for (loop = 0; loop < MAX_PARTICLES; loop=loop+2)
    {
        if (par_sys[loop].alive == true)
        {
            x = par_sys[loop].xpos;
            y = par_sys[loop].ypos;
            z = par_sys[loop].zpos + zoom;
            
            // Draw particles
            glColor3f(1.0, 1.0, 1.0);
            glPushMatrix();
            glTranslatef(x, y, z);
            glutSolidSphere(0.2, 16, 16);
            //sphere2(x,y,z,0.2);
            glPopMatrix();
            
            // Update values
            //Move
            par_sys[loop].ypos += par_sys[loop].vel / (slowdown*1000);
            par_sys[loop].vel += par_sys[loop].gravity;
            // Decay
            par_sys[loop].life -= par_sys[loop].fade;
            
            
            if (par_sys[loop].ypos <= -10)
            {
                par_sys[loop].life = -1.0;
            }
            
            //Revive 
            if (par_sys[loop].life < 0.0)
            {
                initParticles(loop);
            }
        }
    }
    }//if snowstart==1
}

// For Rain
void drawRain()
{
    if(rainstart==1)
    {
    float x, y, z;
    for (loop = 0; loop < MAX_PARTICLES; loop=loop+2)
    {
        if (par_sys[loop].alive == true)
        {
            x = par_sys[loop].xpos;
            y = par_sys[loop].ypos;
            z = par_sys[loop].zpos + zoom;
            
            // Draw particles
            //glColor3f(0.5, 0.5, 1.0);
            glColor3f(0.74902,0.847059,0.847059);
            glBegin(GL_LINES);
            glVertex3f(x, y, z);
            glVertex3f(x, y+1, z);
            glEnd();
            
            // Update values
            //Move
            // Adjust slowdown for speed!
            par_sys[loop].ypos += par_sys[loop].vel / (slowdown*1000);
            par_sys[loop].vel += par_sys[loop].gravity;
            // Decay
            par_sys[loop].life -= par_sys[loop].fade;
            
            if (par_sys[loop].ypos <= -10)
            {
                par_sys[loop].life = -1.0;
            }
            //Revive 
            if (par_sys[loop].life < 0.0)
            {
                initParticles(loop);
            }
        }//if close
    }//for close
    }//if rainstart == 1 close
}//function close



/*
 *  Draw vertex in polar coordinates with normal
 */
static void pVertex(double th,double ph)
{
    double x = Sin(th)*Cos(ph);
    double y = Cos(th)*Cos(ph);
    double z =         Sin(ph);
    //  For a sphere at the origin, the position
    //  and normal vectors are the same
    glNormal3d(x,y,z);
    glVertex3d(x,y,z);
}
/*
 *  Draw a ball
 *     at (x,y,z)
 *     radius (r)
 */
static void ball(double x,double y,double z,double r)
{
    int th,ph;
    float yellow[] = {1.0,1.0,0.0,1.0};
    float Emission[]  = {0.0,0.0,0.01*emission,1.0};
    //  Save transformation
    glPushMatrix();
    //  Offset, scale and rotate
    glTranslated(x,y,z);
    glScaled(r,r,r);
    //  Yellow ball
    glColor3f(1,1,0);
    glMaterialf(GL_FRONT,GL_SHININESS,shiny);
    glMaterialfv(GL_FRONT,GL_SPECULAR,yellow);
    glMaterialfv(GL_FRONT,GL_EMISSION,Emission);
    //  Bands of latitude
    for (ph=-90;ph<90;ph+=inc)
    {
        glBegin(GL_QUAD_STRIP);
        for (th=0;th<=360;th+=2*inc)
        {
            pVertex(th,ph);
            pVertex(th,ph+inc);
        }
        glEnd();
    }
    //  Undo transofrmations
    glPopMatrix();
}

/*
 *  Draw Set of Facets
 */
static void Facets(int k)
{
   int i,j;
   glBegin(GL_TRIANGLES);
   for (i=nFacet[k];i<nFacet[k+1];i++)
      for (j=0;j<3;j++)
      {
         glTexCoord2fv(Texture[Facet[i][2][j]]);
         glNormal3fv(Normal[Facet[i][1][j]]);
         glVertex3fv(Vertex[Facet[i][0][j]]);
      }
   glEnd();
}

/*
 *  Compile F16 display list
 */
static void CompileF16(void)
{
   float black[] = {0,0,0,1};
   int tex[2];

   //  Load textures
   tex[0] = LoadTexBMP("F16s.bmp");
   tex[1] = LoadTexBMP("F16t.bmp");

   //  Body list
   F16[0] = glGenLists(1);
   glNewList(F16[0],GL_COMPILE);
   glColor3f(1,1,1);
   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D,tex[0]);
   Facets(0);
   glDisable(GL_TEXTURE_2D);
   glEndList();

   //  Engine list
   F16[1] = glGenLists(1);
   glNewList(F16[1],GL_COMPILE);
   glColor3f(1,1,1);
   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D,tex[0]);
   Facets(1);
   glDisable(GL_TEXTURE_2D);
   glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);
   glEndList();

   //  Canopy list
   F16[2] = glGenLists(1);
   glNewList(F16[2],GL_COMPILE);
   glColor4f(1,1,1,0.33);
   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D,tex[1]);
   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
   glDepthMask(0);
   Facets(2);
   glDepthMask(1);
   glDisable(GL_BLEND);
   glDisable(GL_TEXTURE_2D);
   glEndList();
}

int bench = 0;
int house = 0;
int firsthouse = 0;
int secondhouse = 0;
int thirdhouse = 0;

void cuboid()
{
 
    float black[] = {0,0,0,1};
    
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);
    
    if(coco==1)
    {
        //glColor3f(1,0.5,0.5);
        glDisable(GL_TEXTURE_2D);
    }
    else
    //cuboid or rectangle structure
    glEnable(GL_TEXTURE_2D);
    
    
  
    
    if(carmodel)
    {
        if(car1==1)
        {
            glColor3f(1,1,1);
            glBindTexture(GL_TEXTURE_2D,sky[5]);
        }//if close
        else if(car2==1)
        {
            glColor3f(1,1,0);
            glBindTexture(GL_TEXTURE_2D,sky[5]);
        }//else if close
        else if(car3==1)
        {
            glColor3f(0.5,0.5,0.5);
            glBindTexture(GL_TEXTURE_2D,sky[5]);
        }//else if close car3
    }
    else
    {
        if(building1==1)
        {
            if(pyramid==1)
            {
                glColor3f(1 ,0.5, 0.0);
                glBindTexture(GL_TEXTURE_2D,sky[7]);
                
            }
            else
            {
                glColor3f(6,0.2,0.5);
                glBindTexture(GL_TEXTURE_2D,sky[7]);
            }
            //glDisable(GL_TEXTURE_2D);
        }
        else
        {
            
            if(teeth==1)
            {
                glEnable(GL_TEXTURE_2D);
                glColor3f(1,1,1);
                glBindTexture(GL_TEXTURE_2D,sky[11]);
            }//if close
            else if(danger==1)
            {
                glColor3f(1,0,0);
                glDisable(GL_TEXTURE_2D);
            }
            else if(fire==1)
            {
                glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D,sky[13]);
            }
            else
            {
            glColor3f(1,1,1);
            glBindTexture(GL_TEXTURE_2D,sky[8]);
            }//else close
        }
    }

    //back
    glBegin(GL_POLYGON);
    glNormal3d(0,0,-1);
    
    if(building1==1)
    {
        glTexCoord2f(0,0);
        glVertex3d(0,0,0);
        glTexCoord2f(1,0);
        glVertex3d(1,0,0);
        glTexCoord2f(1,1);
        glVertex3d(1,1,0);
        glTexCoord2f(0,1);
        glVertex3d(0,1,0);
    }
    else
    {
    glTexCoord2f(0,0);
    glVertex3d(0,0,0);
    glTexCoord2f(1,0);
    glVertex3d(1,0,0);
    glTexCoord2f(1,1);
    glVertex3d(1,1,0);
    glTexCoord2f(0,1);
    glVertex3d(0,1,0);
    }
    
    glEnd();
    
    //front
    glBegin(GL_POLYGON);
    glNormal3d(0,0,1);
    
    if(building1==1)
    {
        glTexCoord2f(0,0); glVertex3d(0,0,1);
        glTexCoord2f(1,0); glVertex3d(1,0,1);
        glTexCoord2f(1,1); glVertex3d(1,1,1);
        glTexCoord2f(0,1); glVertex3d(0,1,1);
    }
    else
    {
    glTexCoord2f(0,0); glVertex3d(0,0,1);
    glTexCoord2f(1,0); glVertex3d(1,0,1);
    glTexCoord2f(1,1); glVertex3d(1,1,1);
    glTexCoord2f(0,1); glVertex3d(0,1,1);
    }
    glEnd();
    
    //top
    glBegin(GL_POLYGON);
    glNormal3d(0,1,0);
    
    if(building1==1)
    {
        glTexCoord2f(0,0); glVertex3d(0,1,0);
        glTexCoord2f(1,0); glVertex3d(1,1,0);
        glTexCoord2f(1,1); glVertex3d(1,1,1);
        glTexCoord2f(0,1); glVertex3d(0,1,1);
    }
    else
    {
    glTexCoord2f(0,0); glVertex3d(0,1,0);
    glTexCoord2f(1,0); glVertex3d(1,1,0);
    glTexCoord2f(1,1); glVertex3d(1,1,1);
    glTexCoord2f(0,1); glVertex3d(0,1,1);
    }
    glEnd();
    
    //bottom
    glBegin(GL_POLYGON);
    glNormal3d(0,-1,0);
    
    if(building1==1)
    {
        glTexCoord2f(0,0); glVertex3d(0,0,0);
        glTexCoord2f(1,0); glVertex3d(1,0,0);
        glTexCoord2f(1,1); glVertex3d(1,0,1);
        glTexCoord2f(0,1); glVertex3d(0,0,1);
    
    }
    else
    {
        glTexCoord2f(0,0); glVertex3d(0,0,0);
        glTexCoord2f(1,0); glVertex3d(1,0,0);
        glTexCoord2f(1,1); glVertex3d(1,0,1);
        glTexCoord2f(0,1); glVertex3d(0,0,1);
    }
    glEnd();
    
    //left
    glBegin(GL_POLYGON);
    glNormal3d(-1,0,0);
    
    if(building1==1)
    {
        glTexCoord2f(0,0); glVertex3d(0,0,0);
        glTexCoord2f(0,1); glVertex3d(0,1,0);
        glTexCoord2f(1,1); glVertex3d(0,1,1);
        glTexCoord2f(1,0); glVertex3d(0,0,1);
    }
    else
    {
        
        glTexCoord2f(0,0); glVertex3d(0,0,0);
        glTexCoord2f(1,0); glVertex3d(0,1,0);
        glTexCoord2f(1,1); glVertex3d(0,1,1);
        glTexCoord2f(0,1); glVertex3d(0,0,1);
    }
    glEnd();
    
    //right
    glBegin(GL_POLYGON);
    glNormal3d(1,0,0);
    
    if(building1==1)
    {
        glTexCoord2f(0,0); glVertex3d(1,0,0);
        glTexCoord2f(0,1); glVertex3d(1,1,0);
        glTexCoord2f(1,1); glVertex3d(1,1,1);
        glTexCoord2f(1,0); glVertex3d(1,0,1);
    }
   else
    {
       glTexCoord2f(0,0); glVertex3d(1,0,0);
       glTexCoord2f(1,0); glVertex3d(1,1,0);
       glTexCoord2f(1,1); glVertex3d(1,1,1);
       glTexCoord2f(0,1); glVertex3d(1,0,1);
    }
    glEnd();
    
    glDisable(GL_TEXTURE_2D);
    
}//rectangle function close

static void Vertexnew(double th,double ph)
{
    //glColor3f(Cos(th)*Cos(th) , Sin(ph)*Sin(ph) , Sin(th)*Sin(th));
    //glVertex3d(Sin(th)*Cos(ph) , Sin(ph) , Cos(th)*Cos(ph));
    double x = Sin(th)*Cos(ph);
    double y = Cos(th)*Cos(ph);
    double z =         Sin(ph);
    //  For a sphere at the origin, the position
    //  and normal vectors are the same
    glNormal3d(x,y,z);
    glTexCoord2d(th/360.0,ph/180.0+0.5);
    if(building1==1)
    {
        glColor3f(0.5,0,0.5);
        //glColor3f(0.576471 ,0.858824 , 0.439216);
        glVertex3d(x,y,z);
    }
    else
    glVertex3d(x,y,z);
}

/*
 *  Draw a sphere (version 2)
 *     at (x,y,z)
 *     radius (r)
 */
static void sphere2(double x,double y,double z,double r)
{
    
    //glColor3f(0,1,0);
    //  Set specular color to white
    float white[] = {1,1,1,1};
    float black[] = {0,0,0,1};
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);

    glEnable(GL_TEXTURE_2D);
    
    glBindTexture(GL_TEXTURE_2D,sky[9]);

    const int d=5;
    int th,ph;

    //  Save transformation
    glPushMatrix();
    //  Offset and scale
    glTranslated(x,y,z);
    glScaled(r,r,r);
    
    
    //  Latitude bands
    for (ph=-90;ph<90;ph+=d)
    {
        glBegin(GL_QUAD_STRIP);
        for (th=0;th<=360;th+=d)
        {
            Vertexnew(th,ph);
            Vertexnew(th,ph+d);
        }
        glEnd();
    }
    glDisable(GL_TEXTURE_2D);

    //  Undo transformations
    glPopMatrix();
}


void frontCar()
{
    
    glPushMatrix();
    
    //texture
    glTranslatef(2,-1,0);
    glScaled(1.5,2,1);
    float black[] = {0,0,0,1};
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);
    
    if(coco==1)
    {
    glDisable(GL_TEXTURE_2D);
        glColor3f(1,1,1);
    }
    else
    //cuboid or rectangle structure
    glEnable(GL_TEXTURE_2D);
    if(car1==1)
    glColor3f(1,1,1);
    else if(car2==1)
        glColor3f(1,1,0);
    else if(car3==1)
        glColor3f(0.5,0.5,0.5);
    glBindTexture(GL_TEXTURE_2D,sky[5]);
    
    if(tree==1)
    {
        //glColor3f(0,1,0);
        //glColor3f(1,1,1);
        glColor3f(0.184314,0.309804,0.184314);
        glBindTexture(GL_TEXTURE_2D,sky[12]);
    }
    
    if(fire==1)
    {
        glColor3f(1,1,1);
        glEnable(GL_TEXTURE_2D);
       glBindTexture(GL_TEXTURE_2D,sky[13]);
        
    }
    
    
    //triangular sides
    //back
    glBegin(GL_POLYGON);
    glNormal3d(0,0,-1);
    glTexCoord2f(0,0); glVertex3d(1,1,0);
    glTexCoord2f(0,1); glVertex3d(1,1.5,0);
    glTexCoord2f(1,0); glVertex3d(1.5,1,0);
    glEnd();
    
    //glColor3f(1,0.3,0.4); - ordinary normal
    //left
    glBegin(GL_POLYGON);
    glNormal3d(-1,0,0);
    glVertex3d(1,1.5,0);
    glVertex3d(1,1,0);
    glVertex3d(1,1,1);
    glVertex3d(1,1.5,1);
    glEnd();
    
    //glColor3f(3,0.6,0.1);
    //front
    glBegin(GL_POLYGON);
    glNormal3d(0,0,1);
    glTexCoord2f(0,0); glVertex3d(1,1,1);
    glTexCoord2f(0,1); glVertex3d(1,1.5,1);
    glTexCoord2f(1,0); glVertex3d(1.5,1,1);
    glEnd();
    
    //right of the triangular structure
    //glColor3f(4,0.4,0.4);
    
    double a1,a2,a3,b1,b2,b3,n1,n2,n3;
    a1= 1.5-1;
    a2= 1-1.5;
    a3= 1-1;
    
    b1= 1-1;
    b2= 1.5-1.5;
    b3= 0-1;
    
    n1 = a2*b3-a3*b2;
    n2 = -(a1*b3 - a3*b1);
    n3 = a1*b2-a2*b1;
    
    glBegin(GL_POLYGON);
    glNormal3d(n1,n2,n3);
    glTexCoord2f(0,0); glVertex3d(1.5,1,0);
    glTexCoord2f(1,0); glVertex3d(1,1.5,0);
    glTexCoord2f(1,1); glVertex3d(1,1.5,1);
    glTexCoord2f(0,1); glVertex3d(1.5,1,1);
    glEnd();
    
    
    glBegin(GL_POLYGON);
    //glColor3f(1,1,1);
    glNormal3d(0,-1,0);
    glVertex3d(1,1,0);
    glVertex3d(1.5,1,0);
    glVertex3d(1.5,1,1);
    glVertex3d(1,1,1);
    glEnd();
    
    glPopMatrix();
    
    glDisable(GL_TEXTURE_2D);
    
    

}//frontCar close

void car()
{
    carmodel=1;
    glPushMatrix();
    glScaled(5,1,1);
    cuboid();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(1,1,0);
    glScaled(2.5,1,1);
    cuboid();
    glPopMatrix();

    frontCar();
    
    glPushMatrix();
    glTranslatef(4.5,0,1);
    glRotated(180,0,1,0);
    frontCar();
    glPopMatrix();
    
   //glColor3f(2,0.7,0.9);
   glColor3f(0,0,0);
   sphere2(1,0,0.3,0.45);
   sphere2(4,0,0.3,0.45);
   sphere2(1,0,0.7,0.45);
   sphere2(4,0,0.7,0.45);
}//car close


// Drawing the bark of the tree - cylinder
void barkDraw(double x,double y, double z, double r)
{
    
    float white[] = {1,1,1,1};
    float black[] = {0,0,0,1};
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
    
    glColor3f(1,1,1);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,sky[3]);
    
    if(cylinder1==1)
        glColor3f(0.3,0.4,5);
        //glColor3f(1,1,1);
    else if(cylinder2==1)
        glColor3f(5,0.4,0.2);
    
    else if(cylinder3==1)
        //glColor3f(0.5,0.3,0.6);
    glColor3f(1,1,0);
    else if(cylinder4==1)
        glColor3f(3,0.5,0.6);
    
    
    
    if(coco==1)
    {
        glColor3f(1,1,0);
        glDisable(GL_TEXTURE_2D);
    }
    
    if(tree==1)
    {
        glColor3f(0.35,0.16,0.14);
        glDisable(GL_TEXTURE_2D);
    }//tree bark
    int incrementCount = 5;
    glPushMatrix();
    //glTranslated(x,y,z);
    glBegin(GL_QUAD_STRIP);
    for (int j=0;j<=360;j+=incrementCount)
    {
        //glColor3f(0.576471 ,0.858824 ,0.439216);
        //glColor3f(colors[0],colors[1],colors[2]);
        const float tc=(j/(float)(2*180));
        glNormal3d(Cos(j),1.0, Sin(j));
        glTexCoord2f(tc,0.0);
        glVertex3f(Cos(j),+1,Sin(j));
        glTexCoord2f(tc,1.0);
        glVertex3f(Cos(j),-1,Sin(j));
    }
    glEnd();
    
    /* top and bottom circles */
    /* reuse the currentTexture on top and bottom) */
    
    glDisable(GL_TEXTURE_2D);
    glColor3f(0,0,0);
    for (int i=1;i>=-1;i-=2)
    {
        glBegin(GL_POLYGON);
    
        if(i==1)
        {
            glNormal3d(0,1,0);
            glVertex3f(0,i,0);
        }//if close
        else
        {
            glNormal3d(0,-1,0);
            glVertex3f(0,i,0);
        }//else close
        
        for (int k=0;k<=360;k+=incrementCount)
        {
            // glTexCoord2f(i*Cos(k),i*Sin(k));
            if(i==1)
            {
                glNormal3d(0,1,0);
                glVertex3f(i*Cos(k),i,Sin(k));
            }//normals for top circle close
            else
            {
                glNormal3d(0,-1,0);
                glVertex3f(i*Cos(k),i,Sin(k));
            }
        }
        glEnd();
        glDisable(GL_TEXTURE_2D);
    }
    glPopMatrix();
}//cylinder close

/*
 *  Draw sky box
 */
static void Sky(double D)
{
   glColor3f(1,1,1);
   glEnable(GL_TEXTURE_2D);
    //  Sides
    if(nightmode==1)
        glBindTexture(GL_TEXTURE_2D,sky[6]);
    else
        glBindTexture(GL_TEXTURE_2D,sky[0]);
    
    //glBindTexture(GL_TEXTURE_2D,sky[10]);
    //left
    glBegin(GL_QUADS);
    glTexCoord2f(0,0);
    glVertex3f(-D,-D,-D);
    glTexCoord2f(1,0);
    glVertex3f(+D,-D,-D);
    glTexCoord2f(1,1);
    glVertex3f(+D,+D,-D);
    glTexCoord2f(0,1);
    glVertex3f(-D,+D,-D);
    glEnd();
    
    //back
    glBegin(GL_QUADS);
    glTexCoord2f(0,0);
    glVertex3f(+D,-D,-D);
    glTexCoord2f(1,0);
    glVertex3f(+D,-D,+D);
    glTexCoord2f(1,1);
    glVertex3f(+D,+D,+D);
    glTexCoord2f(0,1);
    glVertex3f(+D,+D,-D);
    glEnd();
   
    //right
    glBegin(GL_QUADS);
    glTexCoord2f(0,0);
    glVertex3f(+D,-D,+D);
    glTexCoord2f(1,0);
    glVertex3f(-D,-D,+D);
    glTexCoord2f(1,1);
    glVertex3f(-D,+D,+D);
    glTexCoord2f(0,1);
    glVertex3f(+D,+D,+D);
    glEnd();
    
    //front
    glBegin(GL_QUADS);
    glTexCoord2f(0,0);
    glVertex3f(-D,-D,+D);
    glTexCoord2f(1,0);
    glVertex3f(-D,-D,-D);
    glTexCoord2f(1,1);
    glVertex3f(-D,+D,-D);
    glTexCoord2f(0,1);
    glVertex3f(-D,+D,+D);
    glEnd();

   //  Top and bottom
   if(nightmode==1)
       glBindTexture(GL_TEXTURE_2D,sky[6]);
    else
   glBindTexture(GL_TEXTURE_2D,sky[0]);
    
   //top
   glBegin(GL_QUADS);
   glTexCoord2f(0,0);
   glVertex3f(+D,+D,-D);
   glTexCoord2f(1,0);
   glVertex3f(+D,+D,+D);
   glTexCoord2f(1,1);
   glVertex3f(-D,+D,+D);
   glTexCoord2f(0,1);
   glVertex3f(-D,+D,-D);
   glEnd();
    
   
   //bottom
   //laying down roads in the city
   glBindTexture(GL_TEXTURE_2D,sky[4]);
    
    int count=0;
    glBegin(GL_QUADS);
    int p = 40;
    for(int i=0;i<=(2*D);i=i+p)
    {
        glColor3f(0.50, 0.50,0.50);
        if(count%2==0)
        {
            glColor3f(1,1,1);
            if(count==2 || count==4)
            {
                glTexCoord2f(0,0);
                glVertex3f(-D+i,-D+D-35,+D);
                glTexCoord2f(1,0);
                glVertex3f(-D+(i+p),-D+D-35,+D);
                glTexCoord2f(1,1);
                glVertex3f(-D+(i+p),-D+D-35,-D);
                glTexCoord2f(0,1);
                glVertex3f(-D+i,-D+D-35,-D);
            }//if close
            else
            {
                glVertex3f(-D+i,-D+D-35,+D);
                glVertex3f(-D+(i+p),-D+D-35,+D);
                glVertex3f(-D+(i+p),-D+D-35,-D);
                glVertex3f(-D+i,-D+D-35,-D);
            }//else close
        }//if close
        else
        {
            if(count==1)
            {
                glColor3f(1,1,1);
                glTexCoord2f(0,0);
                glVertex3f(-D+i,-D+D-35,+D);
                 glTexCoord2f(1,0);
                glVertex3f(-D+(i+p),-D+D-35,+D);
                 glTexCoord2f(1,1);
                glVertex3f(-D+(i+p),-D+D-35,-D);
                glTexCoord2f(0,1);
                glVertex3f(-D+i,-D+D-35,-D);
            }//count==1
            else
            {
            glVertex3f(-D+i,-D+D-35,+D);
            glVertex3f(-D+(i+p),-D+D-35,+D);
            glVertex3f(-D+(i+p),-D+D-35,-D);
            glVertex3f(-D+i,-D+D-35,-D);
            }//else odd count close
        }
        count++;
    }//for loop close
     glEnd();
    
    glDisable(GL_TEXTURE_2D);
    
    }

int objCount=10;

double xcy[100],zcy[100];
double ys[100],ys1[100],ys2[100];

void randnum_cylinder()
{
    zcy[0] = -100;
    //int d = (int) 3.5*dim;
    for(int i=0;i<objCount;i++)
    {
    //x[i] = (double) (rand() % (2*d))-20;
    //z[i] = (double) (rand() % (2*d))-d;
    zcy[i+1] = zcy[i]+25;
    ys[i]=rand()% (50-30) +30;
    ys1[i]=rand()% (70-50) +50;
    ys2[i]=rand()% (50-30) +30;
    }
}

float angleX = 0.0;
float angleY = 0.0;
float directionX = 0.0;
float directionZ = -1.0;
float directionY = 0.0;
//Ex=0,Ey=0,Ez=0;
float xpos = 0.0;
float ypos = 1.0;
float zpos = 2.0;
//float Cx=0.0,Cy=0.0,Cz=0.0;
int plusminus = 0;

void building(int x,int y,int z)
{
    
    //generating a different structure for the building
    glPushMatrix();
    glTranslated(x,y,z);
    glScaled(20,20,20);
    cuboid();
    glPopMatrix();
    
    glPushMatrix();
    building1=1;
    glTranslated(x,y+20,z);
    //glScaled(20,40,20);
    glScaled(20,5,20);
    cuboid();
    building1=0;
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(x,y+20+5,z);
    glScaled(20,10,20);
    cuboid();
    glPopMatrix();
    
    glPushMatrix();
    building1=1;
    glTranslated(x,y+20+5+10,z);
    //glScaled(20,40,20);
    glScaled(20,5,20);
    cuboid();
    building1=0;
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(x,y+20+5+10+5,z);
    glScaled(20,10,20);
    cuboid();
    glPopMatrix();
    
    glPushMatrix();
    building1=1;
    glTranslated(x,y+20+5+10+5+10,z);
    //glScaled(20,40,20);
    glScaled(20,5,20);
    cuboid();
    building1=0;
    glPopMatrix();
    
}//building function close



void buildingstruct2(int x,int y,int z)
{
    
     glEnable(GL_TEXTURE_2D);
    //generating a different structure for the building
    glPushMatrix();
    glTranslated(x,y,z);
    glScaled(20,20,20);
    cuboid();
    glPopMatrix();
    
    glPushMatrix();
    building1=1;
    glTranslated(x,y+20,z);
    //glScaled(20,40,20);
    glScaled(20,5,20);
    cuboid();
    building1=0;
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(x,y+20+5,z);
    glScaled(20,10,20);
    cuboid();
    glPopMatrix();
    
    glPushMatrix();
    building1=1;
    glTranslated(x,y+20+5+10,z);
    //glScaled(20,40,20);
    glScaled(20,5,20);
    cuboid();
    building1=0;
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(x,y+20+5+10+5,z);
    glScaled(20,10,20);
    cuboid();
    glPopMatrix();
    
    glTranslated(x,y+20+5+10+5+10,z);
    glColor3f(0,0,0);
    building1=1;
    sphere2(10,3,10.5,10);
    building1=0;

}//building function close


void buildingstruct3(int x,int y,int z)
{
    pyramid=1;

    //generating a different structure for the building
    glPushMatrix();
    glTranslated(x,y,z);
    glScaled(20,20,20);
    cuboid();
    glPopMatrix();
    
    glPushMatrix();
    building1=1;
    glTranslated(x,y+20,z);
    //glScaled(20,40,20);
    glScaled(20,5,20);
    cuboid();
    building1=0;
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(x,y+20+5,z);
    glScaled(20,10,20);
    cuboid();
    glPopMatrix();
    
    glPushMatrix();
    building1=1;
    glTranslated(x,y+20+5+10,z);
    glScaled(20,5,20);
    cuboid();
    building1=0;
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(x,y+20+5+10+5,z);
    glScaled(20,10,20);
    cuboid();
    glPopMatrix();
    
    glTranslated(x,y+20+5+10+5+10,z+20);
    glColor3f(0.439216,0.858824,0.576471);
    glScaled(20,10,20);
    glRotated(90,0,1,0);
    
    glEnable(GL_TEXTURE_2D);
   
    glBindTexture(GL_TEXTURE_2D,sky[7]);
    
    //pyramid - front
    glBegin(GL_POLYGON);
    glNormal3d(0,0,1);
    glTexCoord2f(0,0); glVertex3f(0,0,1);
    glTexCoord2f(1,0); glVertex3f(1,0,1);
    glTexCoord2f(0.5,1); glVertex3f(0.5,1,1);
    glEnd();
    
    //back
    glBegin(GL_POLYGON);
    glNormal3d(0,0,-1);
    glTexCoord2f(0,0); glVertex3f(0,0,0);
    glTexCoord2f(1,0); glVertex3f(1,0,0);
    glTexCoord2f(0.5,1); glVertex3f(0.5,1,0);
    glEnd();
    
    //right
    double a1,a2,a3,b1,b2,b3,n1,n2,n3;
    a1= 0-0;
    a2= 0-0;
    a3= 1-0;
    
    b1= 0.5-0;
    b2= 1-0;
    b3= 0-0;
    
    n1 = a2*b3-a3*b2;
    n2 = -(a1*b3 - a3*b1);
    n3 = a1*b2-a2*b1;
    
    glBegin(GL_POLYGON);
    glNormal3d(n1,n2,n3);
    
    glTexCoord2f(0,0);glVertex3f(0,0,0);
    glTexCoord2f(0,1);glVertex3f(0,0,1);
    glTexCoord2f(1,1);glVertex3f(0.5,1,1);
    glTexCoord2f(1,0);glVertex3f(0.5,1,0);
    glEnd();
    
    //left
    b1= 0.5-1;
    b2= 1-0;
    b3= 1-1;
    
    a1= 1-1;
    a2= 0-0;
    a3= 0-1;
    
    n1 = a2*b3-a3*b2;
    n2 = -(a1*b3 - a3*b1);
    n3 = a1*b2-a2*b1;
    
    glBegin(GL_POLYGON);
    glNormal3d(n1,n2,n3);
    glTexCoord2f(0,0);glVertex3f(0.5,1,0);
    glTexCoord2f(0,1);glVertex3f(1,0,0);
    glTexCoord2f(1,1);glVertex3f(1,0,1);
    glTexCoord2f(1,0);glVertex3f(0.5,1,1);
    glEnd();

    pyramid=0;
   
    glDisable(GL_TEXTURE_2D);
    
}//building function close


static void coconutbody()
{
    
    //glColor3f(0,1,0);
    //  Set specular color to white
    float white[] = {1,1,1,1};
    float black[] = {0,0,0,1};
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);
    
    //glEnable(GL_TEXTURE_2D);
    
    //glBindTexture(GL_TEXTURE_2D,sky[10]);
    
    const int d=5;
    int th,ph;
    
    //  Save transformation
    glPushMatrix();
    //  Offset and scale
    
    //  Latitude bands
    for (ph=-90;ph<90;ph+=d)
    {
        glBegin(GL_QUAD_STRIP);
        for (th=0;th<=360;th+=d)
        {
            Vertexnew(th,ph);
            Vertexnew(th,ph+d);
        }
        glEnd();
    }
    //glDisable(GL_TEXTURE_2D);
    
    //  Undo transformations
    glPopMatrix();
}


void coconuts()
{
    glPushMatrix();
    //glColor3f(1,1,1);
    //glColor3f(0.71,0.65,0.26);
    //glColor3f(1,1,1);
    //brown
    glColor3f(0.647059,0.164706,0.164706);
    
    //a little down
    //sphere2(-5,10,0,5);
    //a little up
    //sphere2(-5,15,0,5);
   
    
    //back
    glBegin(GL_POLYGON);
    glNormal3d(0,0,-1);
    //glColor3f(1,0.5,0);
    glVertex3d(0,0,0);
    glVertex3d(1,0,0);
    glVertex3d(1.5,-1,0);
    glVertex3d(1.5,-2,0);
    
    glVertex3d(1,-3,0);
    glVertex3d(0,-3,0);
    glVertex3d(-0.5,-2,0);
    glVertex3d(-0.5,-1,0);
    glEnd();

    //front
    glBegin(GL_POLYGON);
    glNormal3d(0,0,1);
    //glColor3f(1,0.5,0);
    glVertex3d(0,0,1);
    glVertex3d(1,0,1);
    glVertex3d(1.5,-1,1);
    glVertex3d(1.5,-2,1);
    
    glVertex3d(1,-3,1);
    glVertex3d(0,-3,1);
    glVertex3d(-0.5,-2,1);
    glVertex3d(-0.5,-1,1);
    glEnd();
    
    
    // side 1 right
    double a1,a2,a3,b1,b2,b3,n1,n2,n3;
    
    b1= 1-1;
    b2= 0-0;
    b3= 0-1;
    
    a1= 1.5-1;
    a2= -1-0;
    a3= 1-1;
    
    n1 = a2*b3-a3*b2;
    n2 = -(a1*b3 - a3*b1);
    n3 = a1*b2-a2*b1;
    
    glColor3f(6,0.2,0.3);
    glBegin(GL_POLYGON);
    glNormal3d(n1,n2,n3);
    glVertex3d(1,0,0);
    glVertex3d(1,0,1);
    glVertex3d(1.5,-1,1);
    glVertex3d(1.5,-1,0);
    glEnd();
    
    
    // side 2 - right
    glBegin(GL_POLYGON);
    glNormal3d(1,0,0);
    glColor3f(2,0.5,0.6);
    glVertex3d(1.5,-1,1);
    glVertex3d(1.5,-2,1);
    glVertex3d(1.5,-2,0);
    glVertex3d(1.5,-1,0);
    glEnd();

    
    b1= 1.5-1.5;
    b2= -2+2;
    b3= 0-1;
    
    a1= 1-1.5;
    a2= -3+2;
    a3= 1-1;
    
    n1 = a2*b3-a3*b2;
    n2 = -(a1*b3 - a3*b1);
    n3 = a1*b2-a2*b1;
    
    //side 3 - right
    glBegin(GL_POLYGON);
    glNormal3d(n1,n2,n3);
    //glColor3f(6,2,3);
    glColor3f(0.5,0.5,0.5);
    glVertex3d(1.5,-2,1);
    glVertex3d(1,-3,1);
    glVertex3d(1,-3,0);
    glVertex3d(1.5,-2,0);
    glEnd();
    
    
    b1= 0+0.5;
    b2= 0+1;
    b3= 0-0;
    
    a1= -0.5+0.5;
    a2= -1+1;
    a3= 1-0;
    
    n1 = a2*b3-a3*b2;
    n2 = -(a1*b3 - a3*b1);
    n3 = a1*b2-a2*b1;

    
    //left - side 1
    glBegin(GL_POLYGON);
    glNormal3d(n1,n2,n3);
    glColor3f(6,0.2,0.3);
    //glColor3f(0.5,0.5,0.5);
    glVertex3d(0,0,0);
    glVertex3d(0,0,1);
    glVertex3d(-0.5,-1,1);
    glVertex3d(-0.5,-1,0);
    glEnd();
    
    //left side 2
    glBegin(GL_POLYGON);
    glNormal3d(-1,0,0);
    glColor3f(2,0.5,0.6);
    glVertex3d(-0.5,-1,0);
    glVertex3d(-0.5,-2,0);
    glVertex3d(-0.5,-2,1);
    glVertex3d(-0.5,-1,1);
    glEnd();
    
    b1= -0.5-0;
    b2= -2+3;
    b3= 0-0;
    
    a1= 0-0;
    a2= -3+3;
    a3= 1-0;
    
    n1 = a2*b3-a3*b2;
    n2 = -(a1*b3 - a3*b1);
    n3 = a1*b2-a2*b1;
    
    //left side 3
    glBegin(GL_POLYGON);
    glNormal3d(n1,n2,n3);
    glColor3f(0.5,0.5,0.5);
    //glColor3f(6,2,3);
    glVertex3d(-0.5,-2,0);
    glVertex3d(0,-3,0);
    glVertex3d(0,-3,1);
    glVertex3d(-0.5,-2,1);
    glEnd();
    
    //top
    glBegin(GL_POLYGON);
    glNormal3d(0,1,0);
    glVertex3d(1,0,0);
    glVertex3d(1,0,1);
    glVertex3d(0,0,1);
    glVertex3d(0,0,0);
    glEnd();
    
    //bottom
    glBegin(GL_POLYGON);
    glNormal3d(0,-1,0);
    glVertex3d(0,-3,0);
    glVertex3d(1,-3,0);
    glVertex3d(1,-3,1);
    glVertex3d(0,-3,1);
    glEnd();
    glPopMatrix();
    
}//coconuts close


void robot_building()
{
    //robot names! =)
    //glScaled(5,5,5);
    glPushMatrix();
    glTranslatef(-6,21,0.7);
    glScaled(2,2,2);
    glRotated(90,0,1,0);
    coconuts();
    glPopMatrix();
    
    glColor3f(1,1,1);
    glPushMatrix();
    //cocouts sphere translate
    //glTranslatef(-5,11,0);
    glTranslatef(-6,15,2);
    glScaled(3,3,4);
    glRotated(90,0,1,0);
    coconuts();
    //glScaled(5,5,5);
    //coconutbody();
    //coconuts();
    glPopMatrix();
    
    coco=1;
    fire=1;
    glPushMatrix();
    glTranslatef(-5.5,21,-2);
    glScaled(2,1,3);
    cuboid();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-5.5,17,8.5);
    glScaled(2,4,3);
    glRotated(90,0,1,0);
    frontCar();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-3.5,17,-9.5);
    glScaled(2,4,3);
    glRotated(270,0,1,0);
    frontCar();
    glPopMatrix();
    coco = 0;
    
    fire=0;
    
    
    glPushMatrix();
    glColor3f(0,0,0);
    //glTranslatef(-6,14,1.5);
    //glTranslatef(-6,10,1.5);
    glTranslatef(-6,19,0.5);
    glScaled(0.4,0.4,0.4);
    coconutbody();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-6,19,-1);
    glScaled(0.4,0.4,0.4);
    coconutbody();
    glPopMatrix();
    
    
    coco =1;
    teeth=1;
    glPushMatrix();
    glTranslatef(-6.5,16.5,-1.2);
    glScaled(1,1,2);
    cuboid();
    glPopMatrix();
    coco =0;
    teeth=0;
    
    
    danger = 1;
    glColor3f(0,0,0);
    coco =1;
    glPushMatrix();
    glTranslatef(-6.5,12.5,-1.2);
    glScaled(1,1,2);
    glRotated(45,1,0,0);
    cuboid();
    glPopMatrix();
    coco=0;
    
    coco =1;
    glPushMatrix();
    glTranslatef(-6.5,13.5,0);
    glScaled(1,1,2);
    glRotated(45,1,0,0);
    cuboid();
    glPopMatrix();
    coco=0;
    
    coco =1;
    glPushMatrix();
    glTranslatef(-6.5,13.5,-2.4);
    glScaled(1,1,2);
    glRotated(45,1,0,0);
    cuboid();
    glPopMatrix();
    coco=0;
    
    coco =1;
    glPushMatrix();
    glTranslatef(-6.5,12.5,-1.0);
    glScaled(1,1,2);
    glRotated(135,1,0,0);
    cuboid();
    glPopMatrix();
    coco=0;
    
    coco =1;
    glPushMatrix();
    glTranslatef(-6.5,12.5,1.4);
    glScaled(1,1,2);
    glRotated(135,1,0,0);
    cuboid();
    glPopMatrix();
    coco=0;
    danger=0;
    
    coco=1;
    glPushMatrix();
    glTranslatef(-5.5,10.5,4.4);
    glScaled(0.5,1.5,0.5);
    barkDraw(-2,-2,0,3);
    glPopMatrix();
    coco=0;
    
    coco=1;
    glPushMatrix();
    glTranslatef(-5.5,10.5,-4.4);
    glScaled(0.5,1.5,0.5);
    barkDraw(-2,-2,0,3);
    glPopMatrix();
    coco=0;
    
    //hands -right
    coco=1;
    glPushMatrix();
    glTranslatef(-7.5,9.5,4.4);
    //glScaled(5,0.5,0.5);
    glScaled(2,0.5,0.5);
    glRotated(90,0,0,1);
    barkDraw(-2,-2,0,3);
    glPopMatrix();
    coco=0;
    
    //hands-left
    coco=1;
    glPushMatrix();
    glTranslatef(-7.5,9.5,-4.4);
    //glScaled(5,0.5,0.5);
    glScaled(2,0.5,0.5);
    glRotated(90,0,0,1);
    barkDraw(-2,-2,0,3);
    glPopMatrix();
    coco=0;
    
    
    coco=1;
    glPushMatrix();
    glTranslatef(-7.5,9.5,-4.4);
    
    glRotated(90,0,0,1);
    glRotated(45,0,1,0);
    //sword
    glScaled(10,0.5,0.5);
    
    cuboid();
    glPopMatrix();
    coco=0;

    
}//robot_building

void bunch()
{
    //one bunch start
    glPushMatrix();
    glTranslatef(-10,0,0);
    glScaled(10,10,10);
    glRotated(90,0,1,0);
    frontCar();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0,0,-70);
    glScaled(10,10,10);
    glRotated(270,0,1,0);
    frontCar();
    glPopMatrix();
    //one bunch end
    
}//bunch close


void tree_building()
{
    glPushMatrix();
    glTranslatef(0,0,0);
    glRotated(15,1,0,0);
    glScaled(0.5,0.5,0.5);
    bunch();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-1,11,2);
    glRotated(-15,1,0,0);
    glScaled(0.5,0.5,0.5);
    bunch();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-1.2,5,0);
    glRotated(15,1,0,0);
    glScaled(0.5,0.5,0.5);
    bunch();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-1,15,2.5);
    glRotated(-15,1,0,0);
    glScaled(0.5,0.5,0.5);
    bunch();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-2,13,2.5);
    //glRotated(15,1,0,0);
    glScaled(0.5,0.5,0.5);
    bunch();
    glPopMatrix();
    
    //bark
    glPushMatrix();
    glTranslatef(-2.5,5,-16);
    glScaled(1.5,6.5,1.5);
    barkDraw(-2,-2,0,3);
    glPopMatrix();
    
    //decorations
    glColor3f(1,1,1);
    sphere2(-5.5,10,-15,0.5);
    glColor3f(1,0,0);
    sphere2(-6,14,-15,0.5);
    glColor3f(0,1,0);
    sphere2(-6,18,-15,0.5);
    
    glColor3f(1,1,1);
    sphere2(-7,20,-15,0.5);
    
    glColor3f(1,1,1);
    sphere2(-6,12,-14,0.5);
    glColor3f(0,1,0);
    sphere2(-6,16,-17,0.5);
    
    glColor3f(1,0,0);
    sphere2(-6,11,-17,0.5);

    
}//tree_building


/*
 *  OpenGL (GLUT) calls this routine to display the scene
 */
void display()
{
   double D = 3.5*dim;
   //  Erase the window and the depth buffer
   glClearColor(0,0.3,0.7,0);
   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   //  Enable Z-buffering in OpenGL
   glEnable(GL_DEPTH_TEST);
   // glEnable(GL_CULL_FACE);
   //  Undo previous transformations
   glLoadIdentity();
    
   //  Perspective - set eye position
    if(fpn)
    {
        //change these variable names
        gluLookAt(xpos,ypos,zpos,xpos+directionX, ypos+directionY, zpos+directionZ, 0, 1, 0);
    }
    else
        gluLookAt(Ex,Ey,Ez , Ox,Oy,Oz , Ux,Uy,Uz);

    //  Draw sky
    if (box) Sky(3.5*dim);

    //  Flat or smooth shading
    glShadeModel(smooth ? GL_SMOOTH : GL_FLAT);

    //  Light switch
    if (nightlight)
    {
       //  Translate intensity to color vectors
       float Ambient[]   = {0.01*ambient ,0.01*ambient ,0.01*ambient ,1.0};
       float Diffuse[]   = {0.01*diffuse ,0.01*diffuse ,0.01*diffuse ,1.0};
       float Specular[]  = {0.01*specular,0.01*specular,0.01*specular,1.0};
       distance = dim*3.5;
       //  Light position
       float Position[]  = {distance*Cos(zh),ylight,distance*Sin(zh),1.0};
       //  Draw light position as ball (still no lighting here)
       glColor3f(1,1,1);
       ball(Position[0],Position[1],Position[2] , 1);
       //  OpenGL should normalize normal vectors
       glEnable(GL_NORMALIZE);
       //  Enable lighting
       glEnable(GL_LIGHTING);
       //  Location of viewer for specular calculations
       glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,local);
       //  glColor sets ambient and diffuse color materials
       glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
       glEnable(GL_COLOR_MATERIAL);
       //  Enable light 0
       glEnable(GL_LIGHT0);
       //  Set ambient, diffuse, specular components and position of light 0
       glLightfv(GL_LIGHT0,GL_AMBIENT ,Ambient);
       glLightfv(GL_LIGHT0,GL_DIFFUSE ,Diffuse);
       glLightfv(GL_LIGHT0,GL_SPECULAR,Specular);
       glLightfv(GL_LIGHT0,GL_POSITION,Position);
   }
   else
      glDisable(GL_LIGHTING);
    
    if(fog)
    {
        double pp = 40.0*3.5*3.5;
        glEnable(GL_FOG);
        glFogf(GL_FOG_MODE,GL_LINEAR);
        glFogf(GL_FOG_START,1.0);
        glFogf(GL_FOG_END,pp);
        float color[]={0.196078, 0.6,0.8,1.0};
        glFogfv(GL_FOG_COLOR,color);
    }
    else
        glDisable(GL_FOG);
    
    int countp=0;
    // to make the car fall on the road
    int p = 40;
    for(int i=0;i<=(2*D);i=i+p)
    {
        if(countp%2==0)
        {
            glColor3f(1,1,1);
            if(countp==2 || countp==4)
            {
                
                glPushMatrix();
                //glTranslatef(0,0,0);
                if(countp==2)
                {
                    car1=1;
                    glTranslatef(-D+i+20,-35,D-increment);
                }
                else if(countp==4)
                {
                    car2=1;
                    glTranslatef(-D+i+20,-35,-D+increment);
                }
                glRotated(90,0,-1,0);
                //cuboid();
                glScaled(7,7,13);
                car();
                carmodel=0;
                car1=0;
                car2=0;
                glPopMatrix();
            }//if close
            else
            {
            }//else close
        }
        else
        {
            if(countp==1)
            {
                glPushMatrix();
                glColor3f(1,1,1);
                car3=1;
                glTranslatef(-D+i+20,-35,-D+increment);
                glRotated(90,0,-1,0);
                glScaled(7,7,13);
                car();
                car3=0;
                glPopMatrix();
            }//countp==1
        }
        countp++;
    }//for loop close
    
   //building cylindrical buildings
    for(int i=0;i<objCount;i++)
    {
    cylinder1=1;
    glPushMatrix();
    glTranslatef(0,-35,zcy[i]);
    glScaled(10,ys[i],10);
    barkDraw(-2,-2,0,3);
    glPopMatrix();
    cylinder1=0;
    }//generating cylindrical buildings
    
    for(int i=0;i<objCount;i++)
     {
         if(i%2!=0)
         {
             cylinder2=1;
             glPushMatrix();
             glTranslatef(75,-35,zcy[i]);
             //glScaled(3,4,3);
             glScaled(10,ys2[i],10);
             barkDraw(-2,-2,0,3);
             //cuboid();
             glPopMatrix();
             cylinder2=0;
         }//if close
         else
         {
             //generating buildings with cuboids and spheres
             glPushMatrix();
             //glTranslatef(-125,-35,zcy[i]);
             buildingstruct3(75,-35,zcy[i]-10);
             glPopMatrix();
         }//else close
     }//generating cylindrical buildings
   
    for(int i=0;i<objCount;i++)
    {
        if(i%2==0)
        {
        cylinder3=1;
        glPushMatrix();
        glTranslatef(125-20,-35,zcy[i]);
        //glScaled(3,4,3);
        glScaled(14,ys1[i],14);
        barkDraw(-2,-2,0,3);
        glPopMatrix();
        cylinder3=0;
        }
        else
        {
            //generating buildings with cuboids and spheres
            glPushMatrix();
            //glTranslatef(-125,-35,zcy[i]);
            buildingstruct2(125-30,-35,zcy[i]-10);
            glPopMatrix();
        }
    }//generating cylindrical buildings
    
    
    
    
    for(int i=0;i<objCount;i++)
    {
        if(i%2==0)
        {
        cylinder4=1;
        glPushMatrix();
        glTranslatef(-125,-35,zcy[i]);
        //glScaled(3,4,3);
        glScaled(14,ys1[i],14);
        barkDraw(-2,-2,0,3);
        glPopMatrix();
        cylinder4=0;
        }
        else
        {
            //generating buildings with cuboids and spheres
            glPushMatrix();
            //glTranslatef(-125,-35,zcy[i]);
            buildingstruct2(-125,-35,zcy[i]-10);
            glPopMatrix();
        }
    }//generating cylindrical buildings
    
   
    // Which Particles
    if (fall == RAIN)
    {
        drawRain();
    }
    
    else if (fall == SNOW)
        drawSnow();

    //glTranslatef(-6+increment,21,0.7+increment);
    //glTranslatef(120,40,0);
    glPushMatrix();
    glTranslatef(0,0,0);
    glScaled(1,1,1);
    robot_building();
    //robot_building();
    glPopMatrix();
    
    glPushMatrix();
    //left of main robot
    glTranslatef(-D+increment,20,-25);
    glRotated(180,0,1,0);
    robot_building();
    glPopMatrix();
    
    glPushMatrix();
    //right of main robot
    glTranslatef(D-increment,20,25);
    robot_building();
    glPopMatrix();
    
    glPushMatrix();
    //left of main robot
    glTranslatef(-D+increment,20,50);
    glRotated(180,0,1,0);
    robot_building();
    glPopMatrix();
    
    glPushMatrix();
    //right of main robot
    glTranslatef(D-increment,20,-50);
    robot_building();
    glPopMatrix();
   
    glPushMatrix();
    //left of main robot
    glTranslatef(-D+increment,20,-75);
    glRotated(180,0,1,0);
    robot_building();
    glPopMatrix();
    
    glPushMatrix();
    //right of main robot
    glTranslatef(D-increment,20,75);
    robot_building();
    glPopMatrix();
    
    glPushMatrix();
    //left of main robot
    glTranslatef(-D+increment,20,100);
    glRotated(180,0,1,0);
    robot_building();
    glPopMatrix();
    
    glPushMatrix();
    //right of main robot
    glTranslatef(D-increment,20,-100);
    robot_building();
    glPopMatrix();
    
    //tree
    for(int i=-D;i<D;i=i+25)
    {
    glPushMatrix();
    tree=1;
    //glTranslatef(0,0,0);
    glTranslatef(-10,-35,25+i);
    glScaled(1.7,1.7,1.7);
    tree_building();
    tree=0;
    glPopMatrix();
    }//for loop close generating christmas trees
    
    //tree - other side
    for(int i=-D;i<D;i=i+25)
    {
        glPushMatrix();
        tree=1;
        //glTranslatef(0,0,0);
        glTranslatef(15,-35,25+i);
        glRotated(180,0,1,0);
        glScaled(1.7,1.7,1.7);
        tree_building();
        tree=0;
        glPopMatrix();
    }//for loop close generating christmas trees
    
    /*
    fire = 1;
    glPushMatrix();
    glTranslatef(-20-increment,0,0);
    glRotated(15,1,0,0);
    glScaled(0.5,0.5,0.5);
    bunch();
    glPopMatrix();
    fire = 0;
    
    fire = 1;
    glPushMatrix();
    glTranslatef(-10-increment,10,30);
    glRotated(-15,1,0,0);
    glScaled(0.5,0.5,0.5);
    bunch();
    glPopMatrix();
    fire = 0;
    */
    
    
   //Draw axes
   //glDisable(GL_LIGHTING);
    
   glColor3f(1,1,1);
    
   //  Display parameters
   glWindowPos2i(5,5);
   //Print("Angle=%d,%d  Dim=%.1f  Roll %.1f Pitch %.1f Yaw %.1f anglex %f,angleY %f",th,ph,dim,roll,pitch,yaw,angleX,angleY);
    
   if (nightlight)
   {
       Print(" Light=%d,%.1f",zh,Yl);
       Print("Ambient=%d  Diffuse=%d Specular=%d Emission=%d Shininess=%.0f",ambient,diffuse,specular,emission,shiny);
   }//if close
    
   //  Render the scene and make it visible
   ErrCheck("display");
   glFlush();
   glutSwapBuffers();
   
    //car animate
    increment += 1;
    if(increment>=2*D)
    {
        increment = 0;
        //glTranslatef(0,-35,0-increment);
    }//if close
  
    
}

/*
 *  GLUT calls this routine every 50ms
 */
void timer(int toggle)
{
   
      //double D = 3.5*dim;
   
        //if(Ex>= -D && Ex <= D && Ey>= -35 && Ey <= D && Ez>= -D && Ez <= D)
    
      Ex = -2*dim*Sin(th)*Cos(ph);
      Ey = +2*dim        *Sin(ph);
      Ez = +2*dim*Cos(th)*Cos(ph);
        
    
      Ox = Oy = Oz = 0;
    
      X = Y = Z = 0;
    
      Dx = 1; Dy = 0; Dz = 0;
      Ux = 0; Uy = 1; Uz = 0;
   
    //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
   glutTimerFunc(refreshMills, timer, 0); // next timer call milliseconds later

}

/*
 *  GLUT calls this routine when an arrow key is pressed
 */
void special(int key,int x,int y)
{
    
   //  Right arrow key - increase angle by 5 degrees
   if (key == GLUT_KEY_RIGHT)
   {
       if(fpn==2)
       {
           //if(fmod(angleY,5.0)==0)
           angleY += 0.05f;
           //angleY += 0.05f;
           directionX=sin(angleY);
           directionZ=-cos(angleY);
       }
       else
           th += 5;
   }
   //  arrow key - decrease angle by 5 degrees
   else if (key == GLUT_KEY_LEFT)
   {
       if(fpn==2)
       {
           //if(fmod(angleY,5.0)==0)
           angleY -= 0.05f;
           directionX = sin(angleY);
           directionZ = -cos(angleY);
       }
       else
           th -= 5;
   }
   //  Up arrow key - increase elevation by 5 degrees
   else if (key == GLUT_KEY_UP)
   {
     /*  if(fpn==2)
       {
           //th=ph=0;
           //if(fmod(angleX,5.0)==0)
           angleX += 0.05f;
           directionY = sin(angleX);
           directionZ = -cos(angleX);
       }
       else*/
       
           ph += 5;
   }
   //  Down arrow key - decrease elevation by 5 degrees
   else if (key == GLUT_KEY_DOWN)
   {
       /*
       if(fpn==2)
       {
           //ph=th=0;
           //if(fmod(angleX,5.0)==0)
           angleX -= 0.05f;
           directionY = sin(angleX);
           directionZ = -cos(angleX);
       }
       else*/
       
           ph -= 5;
   }
    
 /*   //  PageDown key - decrease dim
   else if (key == GLUT_KEY_PAGE_UP && dim>1)
   {
       dim = dim - 0.1;
       glutPostRedisplay();
   }
   //  PageUp key - increase dim
   else if (key == GLUT_KEY_PAGE_DOWN)
   {
       dim = dim + 0.1;
       glutPostRedisplay();
   }
     //  Keep angles to +/-360 degrees
   */
   th %= 360;
   ph %= 360;
   //  Update projection
   Project(fov,asp,dim);
   //  Update state
   timer(-1);
}

/*
 *  GLUT calls this routine when the window is resized
 */
void idle()
{
    //  Elapsed time in seconds
    double t = glutGet(GLUT_ELAPSED_TIME)/1000.0;
    zh = fmod(90*t,360.0);
    //  Tell GLUT it is necessary to redisplay the scene
    glutPostRedisplay();
}

/*
 *  GLUT calls this routine when a key is pressed
 */
void key(unsigned char ch,int x,int y)
{
    float fraction = 1.3;
   //  Exit on ESC
   if (ch == 27)
      exit(0);
   //  Reset view angle
   else if (ch == '0')
   {
       nightlight=0;
       fpn=0;
       nightmode=0;
       rainstart=0;
       snowstart=0;
       fog=0;
       roll = pitch = yaw = ph = 0;
       th=90;
       if(fpn==2)
       {
           angleX=0.0;
           angleY=0.0;
           th=0;
           ph=0;
           directionX = 0.0;
           directionZ = -1.0;
           directionY = 0.0;
           Ex=0.0,Ey=0.0,Ez=0.0;
           xpos=0.0;
           ypos=1.0;
           zpos=2.0;
           count=1;
       }
       else
       {
           ph = 0;
           th = 90;
       }
   }
   else if (ch == 'm' || ch == 'M')
   {
       //mode = 1-mode;
       fpn=0;
       count=0;
       th=90;
       ph=0;
   }
    //perspective fpn
   else if(ch =='q' || ch == 'Q')
   {
       fpn = 2;
       //mode = 1;
       //count = 1;
       th=0;
       ph=0;
       //th=90;
       if(incre==1)
       {
           angleX=0.0;
           angleY=0.0;
           th=0;
           ph=0;
           //th=90;
           directionX = 0.0;
           directionZ = -1.0;
           directionY = 0.0;
           //xpos=90.0;
           //ypos=1.0;
           //zpos=40.0;
           xpos=40.0;
           ypos=5.0;
           zpos=40.0;
           //Ex=0.0,Ey=0.0,Ez=0.0;
           //xpos = -2*dim*Sin(th)*Cos(ph);
           //ypos = +2*dim        *Sin(ph);
           //zpos = +2*dim*Cos(th)*Cos(ph);
           incre++;
       }
   }
   else if(ch=='x' || ch=='X')
   {
       if(incre>1 && fpn==2)
       {
           //mode = 1;
           //count = 1;
           //th=0;
           th=0;
           ph=0;
           xpos += directionX * fraction;
           zpos += directionZ * fraction;
           ypos += directionY * fraction;
       }
   }//moves forward
   else if(ch=='v' || ch=='V')
   {
       if(incre>1 && fpn==2)
       {
           fpn = 2;
           //mode = 1;
           //count = 1;
           //th=0;
           th=0;
           ph=0;
           xpos -= directionX * fraction;
           ypos -= directionY * fraction;
           zpos -= directionZ * fraction;
       }
   }//moves backward
    else if(ch == 'c')
    {
        nightmode=1;
        nightlight = 1;
    }
   //  Toggle skybox
   else if (ch == 'b' || ch == 'B')
      box = 1-box;
   //  Cycle light
   else if(ch == 'r' || ch == 'R')
    {
        
        fog = 1 - fog;
        
        rainstart = 1 - rainstart;
        fall = RAIN;

        for (int loop = 0; loop < MAX_PARTICLES; loop++)
        {
            initParticles(loop);
        }
        glutPostRedisplay();
    }//rain
    else if(ch == 'w' || ch == 'W')
    {
        //fog=1 - fog;
        fog=0;
        snowstart = 1 - snowstart;
        fall = SNOW;
        
        for (int loop = 0; loop < MAX_PARTICLES; loop++)
        {
            initParticles(loop);
        }
        glutPostRedisplay();
    }//rain
    //  Light elevation
   else if (ch=='[')
       ylight -= 0.1;
   else if (ch==']')
       ylight += 0.1;
    //  Ambient level
   else if (ch=='a' && ambient>0)
       ambient -= 5;
   else if (ch=='A' && ambient<100)
       ambient += 5;
    //  Diffuse level
   else if (ch=='d' && diffuse>0)
       diffuse -= 5;
   else if (ch=='D' && diffuse<100)
       diffuse += 5;
    //  Specular level
   else if (ch=='s' && specular>0)
       specular -= 5;
   else if (ch=='S' && specular<100)
       specular += 5;
    //  Emission level
   else if (ch=='e' && emission>0)
       emission -= 5;
   else if (ch=='E' && emission<100)
       emission += 5;
    //  Shininess level
   else if (ch=='n' && shininess>-1)
       shininess -= 1;
   else if (ch=='N' && shininess<7)
       shininess += 1;
    //  Translate shininess power to value (-1 => 0)
    shiny = shininess<0 ? 0 : pow(2.0,shininess);
   //  Reproject
   Project(fov,asp,dim);
   //  Animate if requested
   glutIdleFunc(move?idle:NULL);
   //  Update state
   timer(-1);
}

/*
 *  GLUT calls this routine when the window is resized
 */
void reshape(int width,int height)
{
   //  Ratio of the width to the height of the window
   asp = (height>0) ? (double)width/height : 1;
   //  Set the viewport to the entire window
   glViewport(0,0, width,height);
   //  Set projection
   Project(fov,asp,dim);
}

/*
 *  Start up GLUT and tell it what to do
 */
int main(int argc,char* argv[])
{

   //  Initialize GLUT
   glutInit(&argc,argv);
   //  Request double buffered, true color window with Z buffering at 600x600
   glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
   glutInitWindowSize(600,600);
   glutCreateWindow("Project_Vaishnavi_Viswanathan");
    // generating radom location coordinates for drawing the cylinder structures
   randnum_cylinder();
   //  Set callbacks
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutSpecialFunc(special);
   glutKeyboardFunc(key);
   glutIdleFunc(idle);
   //  Load and Compile G16
   CompileF16();
   //  Load skybox texture
   sky[0] = LoadTexBMP("skytexture1.bmp");
   sky[1] = LoadTexBMP("skytexture1.bmp");
   sky[2] = LoadTexBMP("grass.bmp");
   sky[3] = LoadTexBMP("pixelcity.bmp");
   sky[4] = LoadTexBMP("road.bmp");
   sky[5] = LoadTexBMP("red.bmp");
   sky[6] = LoadTexBMP("nightsky.bmp");
   sky[7] = LoadTexBMP("roof.bmp");
   sky[8] = LoadTexBMP("stone.bmp");
   sky[9] = LoadTexBMP("dots.bmp");
   sky[10] = LoadTexBMP("coco.bmp");
   sky[11] = LoadTexBMP("monster1.bmp");
   sky[12] = LoadTexBMP("snowcovered.bmp");
   sky[13] = LoadTexBMP("fire.bmp");
    //  Set timer
   timer(1);
   //  Pass control to GLUT so it can interact with the user
   ErrCheck("init");
   glutMainLoop();
   return 0;
}
