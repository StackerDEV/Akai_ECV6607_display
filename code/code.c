
#include <fontALL.h>
#include <TVout.h>

/*
 * MONITOR CAR DVD PLAYER AKAI 
 * Model: ECV6607
 * PCB version: PVS1988-01
 * Schematics: https://diagramas.diagramasde.com/otros2/PVS1950D[1].pdf
 * 
 * Mod to get power supply out of standby mode 
 * D494 (IC902) is from CHCM, TL494 clone.
 * Short PIN 16 IN2+ to PIN 13 DTC OUTPUTCTRL
 * 
 * Video signal injection look at TVout examples
 * See 4 pin header cable VIDEO and VIDEO GROUND it accepts PAL and NTSC (NTSC works best)
 * 
 * TV.begin(NTSC, 145, 100);
 * Max screen width: 142
 * Max screen height: 98
 * 
 * 
 */

TVout TV;

byte graph[80] = { 0 }; // 120 // 80
int graph_len = 79; // 119 // 79

int graph_axis_x = 10; // 10
int graph_axis_y = 94; // 96 // last 94

int cpu_temp = 0;
int nb_temp= 0;
int ram_usage= 0;
int disk_usage= 0;
int net_wan_tx= 0;


void draw_initial_screen() {
  TV.clear_screen();
  TV.draw_rect(0, 0, 127, 25, 1, 0); // Main rect to show all data in
  // draw_column(column,y0,y1,color) 
  TV.draw_column(36,1,23,1);  // CPU temp *C
  TV.draw_column(71,1,23,1); // NB temp *C
  TV.draw_column(103,1,23,1); // Ram use %
  // Disk USE
  // CPU TEMP text
  TV.set_cursor(3, 5); //(x,y) 
  TV.select_font(font4x6);
  TV.print("CPU TEMP");
  // MB TEMP text
  TV.set_cursor(40, 5); //(x,y) 
  TV.select_font(font4x6);
  TV.print("NB TEMP");
  // RAM USE text
  TV.set_cursor(75, 5); //(x,y) 
  TV.select_font(font4x6);
  TV.print("RAMUSE");
  // DISK USE text
  TV.set_cursor(107, 5); //(x,y) 
  TV.select_font(font4x6);
  TV.print("DISK");
  // WAN NETWORK GRAPH
  TV.set_cursor(2, 31); //(x,y) 
  TV.select_font(font6x8);
  TV.print("NET WAN TX:");
}

void setup()  {
  Serial.begin(9600);
  TV.begin(NTSC,128,96); //143,98
  draw_initial_screen();
}

void display_graph(float ct) {
  for (int i = 0; i < graph_len; i++) {
    graph[i] = graph[i + 1];
    TV.set_pixel(i + graph_axis_x, graph_axis_y - graph[i], 1);
    if (graph[i + 1] > 0)
      TV.set_pixel(i + graph_axis_x+1, graph_axis_y - graph[i + 1], 0);
  }
  graph[graph_len] = (byte)ct;
  if (graph[graph_len] > 50) graph[graph_len] = 50;
  TV.draw_column(10,45,94,1); // Graph y axis line left
  TV.draw_column(89,45,94,1); // Graph y axis line right
  TV.draw_line(89,44,127,44,1); // (x0,y0) to (x1,y1). right line under disk box for graph
  TV.draw_row(44,10,2,1); //draw_row(row,x0,x1,color) line in "network socket"
  TV.draw_row(40,5,2,1); // "network socket"
  TV.draw_row(48,5,2,1); // "network socket"

  // Sawtooth y axis of graph
  int pixel_y = 47;
  for (int i = 0; i < 16; i++, pixel_y += 3){
    TV.set_pixel(9,pixel_y,1);  
  }
}

void updateStats(float cpu,float nb, float ram, float disk){
  // CPU TEMP text
  TV.set_cursor(3, 15);
  TV.select_font(font6x8);
  TV.print(cpu, 0);
  (int)cpu > 99 ? TV.print("*C") : TV.print("*C ");
  // MB TEMP text
  TV.set_cursor(39, 15); //(x,y)
  TV.select_font(font6x8);
  TV.print(nb, 0);
  (int)nb > 99 ? TV.print("*C") : TV.print("*C ");
  // RAM USE text
  TV.set_cursor(75, 15); //(x,y)
  TV.select_font(font4x6);
  TV.print(ram, 0);
  TV.print("% ");
  // DISK USE text
  TV.set_cursor(107, 15); //(x,y)
  TV.select_font(font4x6);
  TV.print(disk, 0);
  TV.print("% ");
}

void serialCommunicationData() {
  byte sp = Serial.available();
  if(sp != 0){ // when serial communication is detected
    int cputmp = Serial.parseInt();
    int nbtemp = Serial.parseInt();
    int ramusage = Serial.parseInt();
    int diskusage = Serial.parseInt();
    int wantx = Serial.parseInt();
    if (Serial.read() == '\n') { // read end of message
      cpu_temp = constrain(cputmp, 0, 255);
      nb_temp = constrain(nbtemp, 0, 255);
      ram_usage = constrain(ramusage, 0, 255);
      disk_usage = constrain(diskusage, 0, 255);
      net_wan_tx = constrain(wantx, 0, 255);
      float c = cpu_temp * 1;
      float n = nb_temp * 1;
      float r = ram_usage * 1;
      float d = disk_usage * 1;
      updateStats(c,n,r,d);    
      float graph_data = net_wan_tx;  //float graph_data = random(1, 50);// / 100.0;
      display_graph(graph_data);      
    }
  }
}

void loop() {
  serialCommunicationData(); 
  TV.delay(50);
}