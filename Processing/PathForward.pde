

class PathForward extends PointForward {
  
  ArrayList<PVector> points;
  ArrayList<PVector> pos_5;
  int points_size;
  int acc_t;
  
  PathForward(PImage i, int a, int s, int c) {
    super(i, a, s, c);
    acc_t = a;
    points = new ArrayList<PVector>();
    pos_5 = new ArrayList<PVector>();
    points_size = 0;
  }
  
  PathForward(PImage i, int a, int s, int r, int g, int b) {
    super(i, a, s, r, b, g);
    points = new ArrayList<PVector>();
    points_size = 0;
  }
  
  void filterPoints() {
    for(int i = 0; i < wth*hgt; i++) {
      color c = img.pixels[i];
      if(validColor(c)) {
        int x = i % wth;
        int y = i / wth;
        points.add(new PVector(x, y));
        points_size++;
      }
    }
  }
  
  private int randPick() {
    return int(random(0, points_size));
  }
  
  private int gridPick() {
    int num = int(sqrt(acc_t));
    int del_w = wth / num;
    int del_h = hgt / num;
    int indx = acc_t - acc;
    int indx_w = indx % num;
    int indx_h = indx / num;
    int x = del_w * indx_w;
    int y = del_h * indx_h;
    for(int i = 0; i < points_size; i++) {
      int x_temp = int(points.get(i).x);
      int y_temp = int(points.get(i).y);
      if(x <= x_temp && x_temp < (x + del_w) && y <= y_temp && y_temp < (y + del_h ))
        return i;
    }
    return 0;
  }

  void pickPoints() {
    int i = gridPick();
    int x = int(points.get(i).x);
    int y = int(points.get(i).y);
    pos_1.add(new PVector(x, y));
    pickPointsBound(x, y, pos_2, 2);
    if(acc > 0) {
      acc -= 1;
      pickPoints();
    }
  }
  
  private PVector validDir(int x,int y,int scl, int dir, int del) {
    float dir_r = (dir * PI) / 180;
    float del_x = scl * cos(dir_r);
    float del_y = scl * sin(dir_r);
    int fin_x = x + int(del_x);
    int fin_y = y + int(del_y);
    
    int i = fin_y * wth + fin_x;
    if(i >= img.pixels.length || i < 0)
      return (validDir(x, y, scl, dir + del, del));
    else {
      color c = img.pixels[i];
      if(validColor(c)) {
        return (new PVector(fin_x, fin_y));
      }
      else if(dir >= 360)
        return (validDir(x, y, scl/2, 0, del));
      else
        return (validDir(x, y, scl, dir + del, del));
    }
      
  }
  
  private void pickPointsBound(int x, int y, ArrayList<PVector> p, int i) {
    PVector a = validDir(x, y, scl, 30, 10);
    p.add(a);
    if(i == 2)
      pickPointsBound( int(a.x), int(a.y), pos_3, 3);
    else if(i == 3)
      pickPointsBound( int(a.x), int(a.y), pos_4, 4);
    else if(i == 4)
      pickPointsBound( int(a.x), int(a.y), pos_5, 5);
  }
  
  void drawPoints() {
    for(int i = 0; i < pos_1.size()-1; i++) {
      noFill();
      beginShape();
      curveVertex(pos_1.get(i).x, pos_1.get(i).y);
      curveVertex(pos_2.get(i).x, pos_2.get(i).y);
      curveVertex(pos_3.get(i).x, pos_3.get(i).y);
      curveVertex(pos_4.get(i).x, pos_4.get(i).y);
      curveVertex(pos_5.get(i).x, pos_5.get(i).y);
      endShape();
    }
  }

}