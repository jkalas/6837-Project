import math

class TriangleIndices:
    def __init___(self, v1, v2, v3):
        self.v1 = v1
        self.v2 = v2
        self.v3 = v3

class IcoSphere:

    def __init___(self):
        self.vertices = []
        self.faces = []
        self.index = 0
        self.middlePointIndex = {}

    def addVertex(self, p):
        x = p[0]
        y = p[1]
        z = p[2]
        length = math.sqrt(x * x + y * y + z * z)
        if length > 0:
            self.vertices.append((x / length, y / length, z / length))
        self.index += 1
        return self.index
        
    def getMiddlePoint(self, pos1, pos2):
        smaller = min(pos1, pos2)
        greater = max(pos1, pos2)
        key = (smaller << 32) + greater;

        ret = 0;
        if key in self.middlePointIndex:
            return self.middlePointIndex.get(key)

        pt1 = self.vertices[pos1];
        pt2 = self.vertices[pos2];
        middle = ((pt1[0] + pt2[0]) / 2.0, (pt1[1] + pt2[1]) / 2.0, (pt1[2] + pt2[2]) / 2.0);

        idx = self.addVertex(middle); 

        self.middlePointIndex[key] = idx
        return idx
    

    def create(self, recursionLevel):

        self.vertices = []
        self.faces = []
        self.middlePointIndex = {}
        self.index = 0;

        t = (1.0 + math.sqrt(5.0)) / 2.0;

        self.addVertex((-1,  t,  0));
        self.addVertex(( 1,  t,  0));
        self.addVertex((-1, -t,  0));
        self.addVertex(( 1, -t,  0));

        self.addVertex(( 0, -1,  t));
        self.addVertex(( 0,  1,  t));
        self.addVertex(( 0, -1, -t));
        self.addVertex(( 0,  1, -t));

        self.addVertex(( t,  0, -1));
        self.addVertex(( t,  0,  1));
        self.addVertex((-t,  0, -1));
        self.addVertex((-t,  0,  1));


        faces = []

        faces.append((0, 11, 5));
        faces.append((0, 5, 1));
        faces.append((0, 1, 7));
        faces.append((0, 7, 10));
        faces.append((0, 10, 11));

        faces.append((1, 5, 9));
        faces.append((5, 11, 4));
        faces.append((11, 10, 2));
        faces.append((10, 7, 6));
        faces.append((7, 1, 8));

        faces.append((3, 9, 4));
        faces.append((3, 4, 2));
        faces.append((3, 2, 6));
        faces.append((3, 6, 8));
        faces.append((3, 8, 9));

        faces.append((4, 9, 5));
        faces.append((2, 4, 11));
        faces.append((6, 2, 10));
        faces.append((8, 6, 7));
        faces.append((9, 8, 1));


        for i in range(0, recursionLevel):
            newFaces = [];
            for f in faces:
                v1 = f[0]
                v2 = f[1]
                v3 = f[2]
                
                a = self.getMiddlePoint(v1, v2);
                b = self.getMiddlePoint(v2, v3);
                c = self.getMiddlePoint(v3, v1);

                newFaces.append((v1, a, c));
                newFaces.append((v2, b, a));
                newFaces.append((v3, c, b));
                newFaces.append((a, b, c));
            faces = newFaces;

        for f in faces:
            self.faces.append(f)

        print str(len(self.vertices))
        print str(len(self.faces))

        fileToWrite = open("globe.obj", 'wr')
        for v in self.vertices:
            fileToWrite.write("v " + str(v[0]) + " " + str(v[1]) + " " + str(v[2]) + "\n")

        for f in self.faces:
            fileToWrite.write("f " + str(f[0]) + " " + str(f[1]) + " " + str(f[2]) + "\n")

        fileToWrite.close()
        
i = IcoSphere()
