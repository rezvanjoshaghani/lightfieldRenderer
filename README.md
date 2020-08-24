# lightfieldRenderer
A step by step opengl light filed viewer

# Syntetic camera information

The Camera's position represented by P (this is a point)

The normalized viewing vector represented by v

The Camera's up vector represented by up

The Camera's right vector represented by w (this is the cross product of v X up)

The near distance represented by nDis

The far distance represented by fDis

The field of view represented by fov (this usually in radians)

The aspect ratio represented by ar (this is the width of the screen divided by the height)

To find the corners of the plane at the distance dist:

Hieght = 2 * tan(fov / 2) * dist

Width = Hieght * ar

The center of the plane:

center = P + v * dist

Corner points:

Top Left = center + (up * (Hieght / 2)) - (w * (Width / 2))

Top Right = center + (up * (Hieght / 2)) + (w * (Width / 2))

Bottom Left = center - (up * (Hieght / 2)) - (w * (Width /2))

Bottom Right = center - (up * (Hieght / 2)) + (w * (Width / 2))

