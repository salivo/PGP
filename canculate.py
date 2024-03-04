

import math
import scipy


G_const = scipy.constants.G

debug = False

math.cos

class Body():
    def __init__(self, id, mass, v0, x, y):
        self.mass = mass
        self.v = v0
        self.id = id
        self.pos = [x, y]

    def canculate(self, bodys, t):
        newpos = self.pos

        if debug:
            print("id:",self.id)
        for body in bodys:
            if body.id != self.id:
                #relative cord from body
                rel_x = body.pos[0]-self.pos[0]
                rel_y = body.pos[1]-self.pos[1]
                
                #canculate angle
                angle = math.atan2(abs(rel_y),abs(rel_x)) # in radians!!!!
                
                #canculate distance
                s = 0.5*G_const*body.mass*t**2/(rel_x**2+rel_y**2)+self.v*t

                #canculate new v

                self.v = G_const*body.mass*t**2/(rel_x**2+rel_y**2)*t

                #canculate new posisons
                if rel_y < 0.0:
                    new_rel_y = -1*(s*math.sin(angle))
                else:
                    new_rel_y = s*math.sin(angle)
                
                if rel_x < 0.0:
                    new_rel_x = -1*(s*math.cos(angle))
                else:
                    new_rel_x = s*math.cos(angle)
                newpos[0] += new_rel_x
                newpos[1] += new_rel_y
                if debug:
                    print("Relative posision:", rel_x,rel_y)
                    print("Angle:", math.degrees(angle))
                    print("Distance:", s)
                    print("Speed:", self.v)
                    print("New posision:", new_rel_x, new_rel_y)
        if debug :
            print("Canculated posision:", newpos)




if __name__ == "__main__":
    debug = True
    bodys = [
            Body(1, 1000000, 0, 0, 0),
            Body(2, 1000000, 0, 10, 10),
            Body(3, 1000000, 0, 15, 5)
            ]

    time = 0
    while 1:
        for body in bodys:
            body.canculate(bodys,1000)
        time += 1000
        break



