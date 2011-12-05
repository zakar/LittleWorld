WORLD_WIDTH = 2048
WORLD_HEIGHT = 2048

Tex = {}

function initWorld()

   Tex['map'] = { id = { World.addTexture('./design/Kud01.png', 256, 256) }, 
		  texCoord = { { 1.0, 0.0,  1.0, 1.0,  0.0, 1.0,  0.0, 0.0 } } }

   Tex['player'] = { id = { World.addTexture('./design/player1.png', 128, 128),
			    World.addTexture('./design/player2.png', 128, 128) },
		     texCoord = { { 0.0,1.0,  0.0,0.0,  1.0,0.0, 1.0,1.0 },
				  { 0.0,1.0,  0.0,0.0,  1.0,0.0, 1.0,1.0 } } }

   -- World.addEntity{ Entity = "Floor", 
   -- 		    x = 512, z = 512, s = 2048,
   -- 		    Object = "Sprite",
   -- 		    RGBA = { 1.0, 1.0, 1.0, 1.0 },
   -- 		    totalVertex = 4,
   -- 		    vertex = { 1024,0,1024, 1024,0,-1024, -1024,0,-1024, -1024,0,1024},
   -- 		    normal = { 0,1,0, 0,1,0, 0,1,0, 0,1,0, } }


   for i = 0, WORLD_WIDTH / 128 do
      for j = 0, WORLD_HEIGHT / 128 do 
   	 World.addEntity{ Entity = "Floor", 
   			  x = i*128, z = j*128, s = 128,
   			  Object = "Sprite",
   			  RGBA = { 1.0, 1.0, 1.0, 1.0 },
   			  totalVertex = 4,
   			  vertex = { 64,0,64, 64,0,-64, -64,0,-64, -64,0,64},
   			  normal = { 0,1,0, 0,1,0, 0,1,0, 0,1,0, } }

      end
   end


   World.addEntity{ Entity = "Player",
		    x = 512, z = 512, s = 64,
		    Object = "Sprite",
		    RGBA = { 1.0, 1.0, 1.0, 1.0 },
		    totalVertex = 4,
		    vertex = { 128,0,0,  128,256,0,  -128,256,0,  -128,0,0 },
		    normal = { 0,1,0, 0,1,0, 0,1,0, 0,1,0, } }


   for i = 1,20 do
      World.addEntity{ Entity = "Enemy", 
		       x = math.random(10, 1000), z = math.random(10, 1000), s = 32,
		       Object = "Mesh",
		       RGBA = { 1.0, 0.0, 0.0, 1.0 },
		       size = 32,
		       height = 32 }
   end

   local WallPos = { { x = 1.0, z = 4.0 },
		     { x = 4.0, z = 1.0 },
		     { x = 8.0, z = 7.0 },
		     { x = 6.0, z = 6.0 },
		     { x = 5.0, z = 6.0 },
		     { x = 5.0, z = 5.0 },
		     { x = 5.0, z = 8.0 },
		     { x = 4.0, z = 8.0 },
		     { x = 12.0, z = 8.0 },
		     { x = 11.0, z = 5.0 },
		     { x = 15.0, z = 10.0 },
		     { x = 10.0, z = 13.0 }
		   }

   for i = 1, #WallPos do
      World.addEntity{ Entity = "Wall", 
		       x = WallPos[i].x * 128.0,  z = WallPos[i].z * 128.0,  s = 128.0,
		       Object = "Mesh",
		       RGBA = { 0.3, 0.3, 0.3, 1.0 },
		       size = 128.0, 
		       height = 64.0 }
   end


   World.addLight(256.0, 250.0, 256.0, 1.0, 0.0, 1.0)    
   World.addLight(1280.0, 120.0, 512.0, 0.0, 0.0, 1.0)   
   World.addLight(1024.0, 120.0, 1024.0, 0.0, 1.0, 0.0)  
   World.addLight(640.0, 120.0, 512.0, 1.0, 1.0, 1.0)    
end

