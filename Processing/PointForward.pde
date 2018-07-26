

class PointForward extends Points {
  
  int scl;
  ArrayList<PVector> pos_2;
  ArrayList<PVector> pos_3;
  ArrayList<PVector> pos_4;
  
  PointForward(PImage i, int a, int s, int c) {
    super(i, a, c);
    scl = s;
    pos_2 = new ArrayList<PVector>();
    pos_3 = new ArrayList<PVector>();
    pos_4 = new ArrayList<PVector>();
  }
  
  PointForward(PImage i, int a, int s, int r, int g, int b) {
    super(i, a, r, g, b);
    scl = s;
    pos_2 = new ArrayList<PVector>();
    pos_3 = new ArrayList<PVector>();
    pos_4 = new ArrayList<PVector>();
  }

  void pickPoints() {
    int rand = int(random(0, wth*hgt));
    color c = img.pixels[rand];
    int x = rand % wth;
    int y = rand / wth;
    if(validColor(c)) {
      pos_1.add(new PVector(x,y));
      pickPointsBound(x, y, pos_2);
      pickPointsBound(x, y, pos_3);
      pickPointsBound(x, y, pos_4);
    }
    if(acc > 0) {
      acc -= 1;
      pickPoints();
    }
  }
  
  private void pickPointsBound(int x, int y, ArrayList<PVector> p) {
    int del_x = int(random(-scl, scl));
    int del_y = int(random(-scl, scl));
    int fin_x = x + del_x;
    int fin_y = y + del_y;
    int i = (fin_y) * wth + (fin_x);
    if(img.pixels.length <= i || i < 0)
      pickPointsBound(x, y, p);
    else {
      color c = img.pixels[i];
      if(validColor(c))
        p.add(new PVector(fin_x,fin_y));
      else
        pickPointsBound(x, y, p);
    }
  }
  
  void drawPoints() {
    for(int i = 0; i < pos_1.size()-1; i++) {
      noFill();
      beginShape();
      curveVertex(pos_1.get(i).x, pos_1.get(i).y);
      curveVertex(pos_2.get(i).x, pos_2.get(i).y);
      curveVertex(pos_3.get(i).x, pos_3.get(i).y);
      curveVertex(pos_4.get(i).x, pos_4.get(i).y);
      endShape();
    }
  }

}