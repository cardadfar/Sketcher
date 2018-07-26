int wth;
int hgt;


public void setup() {
  
  //insert dimensions of image here
  size(800,800);
  
  wth = width;
  hgt = height;
  String file = "flower";
  String filetype = ".jpg";
  
  //change for-loop for batch files
  for(int i = 0; i < 1; i++) {
    String k = "0" + str(i);
    background(255);
    
    //for batch files:
    //PImage img = loadImage(file + k + filetype);
    
    PImage img = loadImage(file + filetype);
    PathForward p = new PathForward(img, 3000, 25, 254);
    p.filterPoints();
    p.pickPoints();
    p.drawPoints();
    save(file + "_sketch.jpg");
    println("Rendering image " + str(i) + " out of 2236...");
  }
  println("done!");
}

public class Points { 
  
  PImage img;
  PVector col;
  int acc;
  ArrayList<PVector> pos_1;
  
  Points(PImage i,int a, int c) {
    img = i;
    col = new PVector(c,c,c);
    acc = a;
    pos_1 = new ArrayList<PVector>();
  }
  
  Points(PImage i,int a, int r, int b, int g) {
    img = i;
    col = new PVector(r,b,g);
    acc = a;
    pos_1 = new ArrayList<PVector>();
  }
  
  boolean validColor(color c) {
    boolean red = red(c) < col.x;
    boolean green = green(c) < col.y;
    boolean blue = blue(c) < col.z;
    return (red && green && blue);
  }
  
  void pickPoints() {
  int rand = int(random(0, wth*hgt));
  color c = img.pixels[rand];
  int x = rand % wth;
  int y = rand / wth;
  if(validColor(c))
    pos_1.add(new PVector(x,y));
  if(acc > 0) {
    acc -= 1;
    pickPoints();
    }
  }
  
  void drawPoints() {
    for(int i = 0; i < pos_1.size(); i++) {
      ellipse(pos_1.get(i).x, pos_1.get(i).y, 5, 5);
    }
  }
} 