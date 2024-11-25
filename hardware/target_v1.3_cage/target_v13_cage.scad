pcb_x = 29.0;
pcb_y = 25.0;
pcb_z1 = 1.75;
pcb_z2 = 3.3;


// unregular cube
// 4 of the 12 edges are rounded
module round_cuboid(x,y,z,r,$fn=48) 
{
    cube([x,y-2*r,z],center=true);
    cube([x-2*r,y,z],center=true);
    cube([x-2*r,y-2*r,z],center=true);
    
    translate([+x/2-r,+y/2-r,0]) cylinder(r=r,h=z,center=true);
    translate([+x/2-r,-y/2+r,0]) cylinder(r=r,h=z,center=true);
    translate([-x/2+r,+y/2-r,0]) cylinder(r=r,h=z,center=true);
    translate([-x/2+r,-y/2+r,0]) cylinder(r=r,h=z,center=true);
}   

// unregular cube
// all 12 edges are rounded
module round_cuboid3(x,y,z,r,$fn=48) 
{
    cube([x,y-2*r,z-2*r],center=true);
    cube([x-2*r,y,z-2*r],center=true);
    cube([x-2*r,y-2*r,z],center=true);
    
    translate([+x/2-r,+y/2-r,0]) cylinder(r=r,h=z-2*r,center=true);
    translate([+x/2-r,-y/2+r,0]) cylinder(r=r,h=z-2*r,center=true);
    translate([-x/2+r,+y/2-r,0]) cylinder(r=r,h=z-2*r,center=true);
    translate([-x/2+r,-y/2+r,0]) cylinder(r=r,h=z-2*r,center=true);

    translate([+x/2-r,0,+z/2-r]) rotate([90,0,0]) cylinder(r=r,h=y-2*r,center=true);
    translate([+x/2-r,0,-z/2+r]) rotate([90,0,0]) cylinder(r=r,h=y-2*r,center=true);
    translate([-x/2+r,0,+z/2-r]) rotate([90,0,0]) cylinder(r=r,h=y-2*r,center=true);
    translate([-x/2+r,0,-z/2+r]) rotate([90,0,0]) cylinder(r=r,h=y-2*r,center=true);
    
    translate([0,+y/2-r,+z/2-r]) rotate([0,90,0]) cylinder(r=r,h=x-2*r,center=true);
    translate([0,+y/2-r,-z/2+r]) rotate([0,90,0]) cylinder(r=r,h=x-2*r,center=true);
    translate([0,-y/2+r,+z/2-r]) rotate([0,90,0]) cylinder(r=r,h=x-2*r,center=true);
    translate([0,-y/2+r,-z/2+r]) rotate([0,90,0]) cylinder(r=r,h=x-2*r,center=true);
    
    translate([+(x/2-r),+(y/2-r),+(z/2-r)]) sphere(r=r);
    translate([+(x/2-r),+(y/2-r),-(z/2-r)]) sphere(r=r);
    translate([+(x/2-r),-(y/2-r),+(z/2-r)]) sphere(r=r);
    translate([+(x/2-r),-(y/2-r),-(z/2-r)]) sphere(r=r);
    translate([-(x/2-r),+(y/2-r),+(z/2-r)]) sphere(r=r);
    translate([-(x/2-r),+(y/2-r),-(z/2-r)]) sphere(r=r);
    translate([-(x/2-r),-(y/2-r),+(z/2-r)]) sphere(r=r);
    translate([-(x/2-r),-(y/2-r),-(z/2-r)]) sphere(r=r);
}


module target13() 
{
    // cutouts
    union() {
        // PCB + Parts (large cutout)
        translate([0,0,pcb_z1/2]) round_cuboid(x=pcb_x+0.1, y=pcb_y+0.1, z=pcb_z1+0.1,r=1);
        translate([0,0,pcb_z2/2]) round_cuboid(x=pcb_x-2*0.6, y=pcb_y-2*0.6, z=pcb_z2,r=1);
        // cutout below
        translate([0,0,-pcb_z2/2]) round_cuboid(x=29-2*0.4, y=25-2*0.40, z=pcb_z2,r=1);

        // Connector
        translate([-pcb_x/2,0,3.3/2]) cube([10,21,3.3], center=true);
        translate([-(pcb_x+10-0.2)/2,0,3.3/2]) cube([10,21,20], center=true);
        translate([-pcb_x/2-0.2,0,-2]) cube([10,21,4], center=true);
        
        // SMA-Connector
        translate([+pcb_x/2,0,3.3/2]) cube([10,21,3.3], center=true);
        translate([+(pcb_x+10-0.2)/2,0,3.3/2]) cube([10,21,20], center=true);
        translate([+pcb_x/2-0.2,0,-2]) cube([10,21,4], center=true);

        // Side-cutouts
        translate([+7.0,0,0]) cube([10,pcb_y+10,2*pcb_z2], center=true);
        translate([-7.0,0,0]) cube([10,pcb_y+10,2*pcb_z2], center=true);
    }
}

module window_honey_neg()
{
    // honey comb top
    // easy way to tune line-thickness -> d_cylinder
    intersection () {
        translate([0,0,pcb_z2]) round_cuboid(x=pcb_x-4.0, y=pcb_y-1.0, z=pcb_z2, r=1);
        for (i = [-5:1:5], j=[-5:1:10]) {
            translate([i*5.0,i*3.0 + j*6,0]) cylinder(h=25, d=5.7, $fn=6);
        }
    }   
}

module cage()
{
    difference () {
        translate([0,0,pcb_z2/2]) round_cuboid3(x=pcb_x+2*1.5, y=pcb_y+2*1.5, z=pcb_z2+2*1, r=1);
        window_honey_neg();
        target13();
    }
}


//target13();
//window_honey_neg();
cage();