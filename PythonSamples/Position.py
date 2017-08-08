class Position():
	'3d spatial location and rotation within a virtual space of form x y z zr xr yr'
	def __init__(self, x = 0, y = 0, z = 0, xr = 0, yr = 0, zr = 0):
		self.x = x
		self.y = y
		self.z = z
		self.xr = xr
		self.yr = yr
		self.zr = zr
		self.position = [self.x,self.y,self.z,self.xr,self.yr,self.zr]
		self.location = [self.x,self.y,self.z]
		self.rotation = [self.xr,self.yr,self.zr]
	def set_x(self,nX):
		self.x = nX
		self.position[0] = self.x
		self.location[0] = self.x
	def inc_x(self,dX):
		self.x += dX
		self.position[0] = self.x
		self.location[0] = self.x
	def get_x(self):
		return(self.x)
	def set_y(self,nY):
		self.y = nY
		self.position[1] = self.y
		self.location[1] = self.y
	def inc_y(self,dY):
		self.y += dY
		self.position[1] = self.y
		self.location[1] = self.y
	def get_y(self):
		return(self.y)
	def set_z(self, nZ):
		self.z = z
		self.position[2] = self.z
		self.location[2] = self.z
	def inc_z(self,dZ):
		self.z += dZ
		self.position[2] = self.z
		self.location[2] = self.z
	def get_z(self):
		return(self.z)
	def set_xr(self,nXR):
		self.xr = nXR
		self.position[3] = self.xr
		self.rotation[0] = self.xr
	def inc_xr(self,dXR):
		self.position[3] = self.xr
		self.rotation[0] = self.xr
		self.xr += dXR
	def get_xr(self):
		return(self.xr)
	def set_yr(self,nYR):
		self.yr = nYR
		self.position[4] = self.yr
		self.rotation[1] = self.yr
	def inc_yr(self,dXR):
		self.yr += dXR
		self.position[4] = self.yr
		self.rotation[1] = self.yr
	def get_yr(self):
		return(self.yr)
	def set_zr(self,nZR):
		self.zr = nZR
		self.position[5] = self.zr
		self.rotation[2] = self.zr
	def inc_zr(self,dZR):
		self.zr += dZR
		self.position[5] = self.zr
		self.rotation[2] = self.zr
	def get_zr(self):
		return(self.zr)
	def set_position(self,nX,nY,nZ,xR,yR,zR):
		self.position = [nX,nY,nZ,xR,yR,zR]
		self.x = nX
		self.y = nY
		self.z = nZ
		self.xr = xR
		self.yr = yR
		self.zr = zR
		self.location = [nX,nY,nZ]
		self.rotation = [xR,yR,zR]
	def get_position(self):
		return(self.position)
	def set_location(self,nX,nY,nZ):
		self.location = [nX,nY,nZ]
		self.x = nX
		self.y = nY
		self.z = nZ
		self.position[0] = nX
		self.position[1] = nY
		self.position[2] = nZ
	def get_location(self):
		return(self.location)
	def set_rotation(self, nXR, nYR, nZR):
		self.rotation = [nXR,nYR,nZR]
		self.position[3] = nXR
		self.position[4] = nYR
		self.position[5] = nZR
	def get_rotation(self):
		return(self.rotation)
	def __str__(self):
		return("Position at X:{0},Y:{1},Z:{2},XR:{3},YR:{4},ZR:{5}".format(self.x,self.y,self.z,self.xr,self.yr,self.zr))
