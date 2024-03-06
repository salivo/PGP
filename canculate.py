

import math
import scipy


G_const = scipy.constants.G

debug = True


class Body():
    def __init__(self, id, mass, vx0, vy0, x, y):
        self.mass = mass
        self.vx = vx0
        self.vy = vy0
        self.id = id
        self.pos = [x, y]

    def canculate(self, bodys, dt):
        
        temp_sy = 0
        temp_sx = 0

        if debug:
            print("id:",self.id)

        for body in bodys:
            if body.id != self.id:
                #relative cord from body
                rel_x = body.pos[0]-self.pos[0]
                rel_y = body.pos[1]-self.pos[1]
                # canculate angle
                angle = math.atan2(rel_y, rel_x)
                # canculate acceleration
                ax = (G_const * body.mass * math.cos(angle)) / (rel_x**2+rel_y**2)
                ay = (G_const * body.mass * math.sin(angle)) / (rel_x**2+rel_y**2)

                #canculate distance
                temp_sx += 0.5*ax*dt**2+self.vx*dt
                temp_sy += 0.5*ay*dt**2+self.vy*dt
                #canculate new v
                self.vx += ax*dt
                self.vy += ay*dt
                if debug:
                    print("Relative pos:", rel_x,rel_y)
                    print("Angle:", math.degrees(angle))
                    print("ds:", temp_sx, temp_sy)
                    print("V:", self.vx, self.vy)
        self.pos[0] += temp_sx
        self.pos[1] += temp_sy





if __name__ == "__main__":
    debug = True
    bodys = [
            Body(1, 1000000, 0, 0, 0,  0),
            Body(2, 1000000, 0, 0, 10, 10),        
            ]

    time = 0
    while 1:
        for body in bodys:
            body.canculate(bodys,0.1)
        time += 1



