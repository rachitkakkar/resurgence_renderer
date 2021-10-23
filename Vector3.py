from math import sqrt

class Vector3:  # Vector3 Class
    def __init__(self, x, y, z):
        self.x = x
        self.y = y
        self.z = z

    def __add__(self, other_Vector3):  # Adding vector with another vector
        return Vector3(self.x + other_Vector3.x, self.y + other_Vector3.y, self.z + other_Vector3.z)

    def __sub__(self, other_Vector3):  # Subtracting vector with another vector
        return Vector3(self.x - other_Vector3.x, self.y - other_Vector3.y, self.z - other_Vector3.z)

    def __mul__(self, n):  # Multiplying vector with a number
        return Vector3(self.x * n, self.y * n, self.z * n)

    def __rmul__(self, n):  # Multiplying vector with a number (on the other side)
        return Vector3(self.x * n, self.y * n, self.z * n)

    def __truediv__(self, n):  # Dividing vector with a number
        return Vector3(self.x / n, self.y / n, self.z / n)

    def __str__(self):  # Representation method
        return "({}, {}, {})".format(self.x, self.y, self.z)

    def dot_product(self, other_Vector3):  # dot product
        return self.x * other_Vector3.x + self.y * other_Vector3.y + self.z * other_Vector3.z

    def normalize(self):  # Normalize vector
        magnitude = sqrt(self.x * self.x + self.y * self.y + self.z * self.z)
        return Vector3(self.x / magnitude, self.y / magnitude, self.z / magnitude)

    def negative(self):  # Multiply x, y, and z by -1
        return Vector3(self.x * -1, self.y * -1, self.z * -1)

    def to_color(self):  # Formatting to and rgb color
        r = int(self.x)
        b = int(self.y)
        g = int(self.z)

        if (r > 255): r = 255
        if (r < 0): r = 0
        if (b > 255): b = 255
        if (b < 0): b = 0
        if (g > 255): g = 255
        if (g < 0): g = 0

        return Vector3(r, b, g)

    def to_tuple(self):  # Converting to a tuple
        return (self.x, self.y, self.z)
