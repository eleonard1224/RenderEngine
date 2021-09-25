# Import libraries
import bpy  

# Inputs
obj_name = 'Plane'
output_file = '/home/rick/Documents/Syllabus/CPP/RenderEngine/meshes/square.csv'

# Calculations
obj = bpy.data.objects[obj_name]
faces = obj.data.polygons
nfaces = len(faces)
vertices = obj.data.vertices
vertices_by_face_0 = [ obj.matrix_world @ vertices[f.vertices[0]].co for f in faces ]
vertices_by_face_1 = [ obj.matrix_world @ vertices[f.vertices[1]].co for f in faces ]
vertices_by_face_2 = [ obj.matrix_world @ vertices[f.vertices[2]].co for f in faces ]
vertices_by_face = []
for i in range(nfaces):
    vertices_by_face += [vertices_by_face_0[i][0], vertices_by_face_0[i][1], vertices_by_face_0[i][2],
    vertices_by_face_1[i][0], vertices_by_face_1[i][1], vertices_by_face_1[i][2], 
    vertices_by_face_2[i][0], vertices_by_face_2[i][1], vertices_by_face_2[i][2]]

## Save to File
csvLines = [ ''.join([ str(vertices_by_face[i]) + ',' + str(vertices_by_face[i+1]) + ',' 
    + str(vertices_by_face[i+2]) + ',' + str(vertices_by_face[i+3]) + ',' + str(vertices_by_face[i+4])
    + ',' + str(vertices_by_face[i+5]) + ',' + str(vertices_by_face[i+6])
    + ',' + str(vertices_by_face[i+7]) + ',' + str(vertices_by_face[i+8])
    ]) + "\n" for i in range(0,9*nfaces,9) ]
f = open( output_file, 'w' )
f.writelines( csvLines )
f.close()