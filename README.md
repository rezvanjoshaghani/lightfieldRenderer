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

First we will get the width and height of the near plane

Hnear = 2 * tan(fov / 2) * nDis

Wnear = Hnear * ar

Then we do the same for the far plane

Hfar = 2 * tan(fov / 2) * fDis

Wfar = Hfar * ar

Now we get the center of the planes

Cnear = P + v * nDis

Cfar = P + v * fDis

And now we get our points

Near Top Left = Cnear + (up * (Hnear / 2)) - (w * (Wnear / 2))

Near Top Right = Cnear + (up * (Hnear / 2)) + (w * (Wnear / 2))

Near Bottom Left = Cnear - (up * (Hnear / 2)) - (w * (Wnear /2))

Near Bottom Right = Cnear - (up * (Hnear / 2)) + (w * (Wnear / 2))

Far Top Left = Cfar + (up * (Hfar / 2)) - (w * Wfar / 2))

Far Top Right = Cfar + (up * (Hfar / 2)) + (w * Wfar / 2))

Far Bottom Left = Cfar - (up * (Hfar / 2)) - (w * Wfar / 2))

Far Bottom Right = Cfar - (up * (Hfar / 2)) + (w * Wfar / 2))
