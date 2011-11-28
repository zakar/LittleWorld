WORLD_WIDTH = 2048
WORLD_HEIGHT = 2048

TexId = {}

function initWorld()

   TexId['map'] = World.addTexture('./design/map.png', 64, 64)
   TexId['player0'] = World.addTexture('./design/player1.png', 128, 128)
   TexId['player1'] = World.addTexture('./design/player2.png', 128, 128)

   for i = 0, WORLD_WIDTH / 128 do
      for j = 0, WORLD_HEIGHT / 128 do 
	 World.addEntity{ Entity = "Floor", 
			  x = i*128, z = j*128, s = 128,
			  Object = "Sprite",
			  RGBA = { 1.0, 1.0, 1.0, 1.0 },
			  totalVertex = 4,
			  vertex = { 64,0,64, 64,0,-64, -64,0,-64, -64,0,64},
			  normal = { 0,1,0, 0,1,0, 0,1,0, 0,1,0, },
			  texCoord = { 0.3, 0.0,  0.3, 0.3,  0.0, 0.3,  0.0, 0.0 }  }
      end
   end



   World.addEntity{ Entity = "Player",
		    x = 512, z = 512, s = 64,
		    Object = "Sprite",
		    RGBA = { 1.0, 1.0, 1.0, 1.0 },
		    totalVertex = 4,
		    vertex = { 128,0,0,  128,256,0,  -128,256,0,  -128,0,0 },
		    normal = { 0,1,0, 0,1,0, 0,1,0, 0,1,0, },
		    texCoord = { 0.0,1.0,  0.0,0.0,  1.0,0.0, 1.0,1.0 } }


   for i = 1,20 do
      World.addEntity{ Entity = "Enemy", 
		       x = math.random(10, 1000), z = math.random(10, 1000), s = 32,
		       Object = "Mesh",
		       RGBA = { 1.0, 0.0, 0.0, 1.0 },
		       size = 32,
		       height = 32 }
   end

   World.addEntity{ Entity = "Wall", 
		    x = 1.0 * 128.0,  z = 4.0 * 128.0, s = 128.0,
		    Object = "Mesh",
		    RGBA = { 0.3, 0.3, 0.3, 1.0 },
		    size = 128.0, 
		    height = 64.0 }

   World.addLight(256.0, 250.0, 256.0, 1.0, 0.0, 1.0)    
   World.addLight(1280.0, 120.0, 512.0, 0.0, 0.0, 1.0)   
   World.addLight(1024.0, 120.0, 1024.0, 0.0, 1.0, 0.0)  
end



-- World.addWallDecor(4.0 * 128.0, 1.0 * 128.0, 128.0)
-- World.addWallDecor(8.0 * 128.0, 7.0 * 128.0, 32.0)
-- World.addWallDecor(6.0 * 128.0, 6.0 * 128.0, 48.0)
-- World.addWallDecor(5.0 * 128.0, 6.0 * 128.0, 96.0)
-- World.addWallDecor(5.0 * 128.0, 5.0 * 128.0, 64.0)
-- World.addWallDecor(5.0 * 128.0, 8.0 * 128.0, 64.0)
-- World.addWallDecor(4.0 * 128.0, 8.0 * 128.0, 64.0)
-- World.addWallDecor(12.0 * 128.0, 8.0 * 128.0, 24.0)
-- World.addWallDecor(11.0 * 128.0, 5.0 * 128.0, 48.0)
-- World.addWallDecor(15.0 * 128.0, 10.0 * 128.0, 32.0)
-- World.addWallDecor(10.0 * 128.0, 13.0 * 128.0, 64.0)

--   World.addLight(640.0, 120.0, 512.0, 1.0, 1.0, 1.0)    
