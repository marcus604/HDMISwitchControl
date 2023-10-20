$fn=50;

width = 28.5;
depth = 49.5;
height = 15;

cutThreshold = 4;

difference() {
    
    minkowski() {
        cube([width+1, depth+1, height+1], center = true);
        
        sphere(1);
    }



    //cut off the top
    translate([0,0,height-5]) cube([width+cutThreshold, depth+cutThreshold, height+cutThreshold], center = true);
    
    //hollow the inside

    minkowski() {
        cube([width-1,depth-1,height-1], center = true);
        sphere(1);
    }



//lid
translate([0,0,-1]) 
linear_extrude(20) {
    
    minkowski() {
        square([width, depth], center = true);
        circle(1);
    }
}

}


