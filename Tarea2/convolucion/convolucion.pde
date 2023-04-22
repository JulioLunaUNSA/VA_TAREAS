import g4p_controls.*;

String arch = G4P.selectInput("Arbir imagen", "jpg,png", "Abrir");

float filtro[][] = {
 {-1,-1,-1},
 {-1,8,-1},
 {-1,-1,-1}
};

float filtro1[][] = {
 {0,-1,0},
 {-1,5,-1},
 {0,-1,0}
};

float k = sqrt(2);

float filtro2[][] = {
 {1/(2+k),0,-1/(2+k)},
 {k/(2+k),0,-k/(2+k)},
 {1/(2+k),0,-1/(2+k)}
};

float filtro3[][] = {
 {-1/(2+k),-k/(2+k),-1/(2+k)},
 {0,1/(2+k),0},
 {1/(2+k),0,-1/(2+k)}
};

void setup(){
 size(640, 480);
 PImage img = loadImage(arch);
 PImage procesada = convolucion(img, filtro);
 image(img,0,0);
 image(procesada,img.width,0);
}

PImage convolucion(PImage img1, float [][]mascara) {
  int x,y,i,j,k,l;
  int mitad;
  int inicio, fin;
  int tam = mascara.length;
  PImage img2 = createImage( img1.width, img1.height, RGB);
  img1.loadPixels();
  img2.loadPixels();
  
  mitad = int(tam/2);
  inicio = -mitad;
  fin = mitad;
  
  float r,g,b;
  
  for( y = mitad; y<img1.height - mitad; y++) {
     for( x =mitad; x<img1.width - mitad; x++) {
       r = 0;
       g = 0;
       b = 0;
       int loc1 = x +y*img1.width;
       
       for (j = inicio, l=0; j<=fin; j++, l++) {
         for ( i = inicio, k=0; i<= fin; i++, k++) {
           int loc2 = (x+1) + ((y + j)* img1.width);
           r += red(img1.pixels[loc2])* mascara[k][l];
           g += green(img1.pixels[loc2])* mascara[k][l];
           b += blue(img1.pixels[loc2])* mascara[k][l];
         }
       }       
       img2.pixels[loc1] = color(r,g,b);
     }
  }
  img2.updatePixels();
  return img2;
}
