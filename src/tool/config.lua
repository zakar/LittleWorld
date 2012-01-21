WORLD_WIDTH = 2048
WORLD_HEIGHT = 2048

Tex = {}

Tex['map'] = { id = World.addTexture('./design/grass.jpg', 128, 128), 
	       texCoord = { 1.0, 0.0,  1.0, 1.0,  0.0, 1.0,  0.0, 0.0 } }

Tex['goal'] = { id = World.addTexture('./design/Kud01.png', 128, 128),
		texCoord = { 1.0, 0.0,  1.0, 1.0,  0.0, 1.0,  0.0, 0.0 } }

Tex['player'] = { id = {} }
for i = 1,4 do
   for j = 1,4 do
      Tex['player'].id[i..j] = World.addTexture('./design/ameng/' .. i .. j .. '.png', 128, 128)
   end
end
Tex['player'].texCoord = { 0.0,1.0,  0.0,0.0,  1.0,0.0, 1.0,1.0 }
Tex['player'].alpha_test = true


Tex['enemy'] = { id = {} }
for i = 1,4 do
   Tex['enemy'].id[i] = World.addTexture('./design/elizabeth' .. i .. '.png', 128, 128)
end
Tex['enemy'].texCoord = { 0.0,1.0,  0.0,0.0,  1.0,0.0, 1.0,1.0 }
Tex['enemy'].alpha_test = true

Tex['background'] = { id = { World.addTexture('./design/background1.jpg', 1024, 512) } }


   local WallPos = { 	 { x = 2.0 , z = 4.0 },
			 { x = 5.0 , z = 4.0 },
			 { x = 6.0 , z = 4.0 },
			 { x = 6.0 , z = 4.0 },
			 { x = 7.0 , z = 4.0 },
			 { x = 8.0 , z = 4.0 },
			 { x = 9.0 , z = 4.0 },
			 { x = 8.0 , z = 6.0 },
			 { x = 3.0 , z = 8.0 },
			 { x = 4.0 , z = 8.0 },
			 { x = 5.0 , z = 8.0 },
			 { x = 5.0 , z = 8.0 },
			 { x = 5.0 , z = 10.0 },
			 { x = 6.0 , z = 10.0 },
			 { x = 7.0 , z = 10.0 },
			 { x = 8.0 , z = 10.0 },
			 { x = 9.0 , z = 10.0 },
			 { x = 10.0 , z = 10.0 },
			 { x = 3.0 , z = 10.0 },
			 { x = 4.0 , z = 12.0 },
			 { x = 7.0 , z = 12.0 },
			 { x = 8.0 , z = 12.0 },
			 { x = 11.0 , z = 12.0 },
			 { x = 12.0 , z = 12.0 },
			 { x = 13.0 , z = 12.0 },
			 { x = 14.0 , z = 12.0 },
			 { x = 15.0 , z = 12.0 },
			 -- { x = 16.0 , z = 12.0 },
			 { x = 7.0 , z = 13.0 },
			 { x = 7.0 , z = 14.0 },
			 { x = 7.0 , z = 15.0 },
			 { x = 7.0 , z = 16.0 },
			 { x = 10.0 , z = 4.0 },
			 { x = 1.0 , z = 1.0 },
			 { x = 5.0 , z = 1.0 },
			 { x = 9.0 , z = 1.0 },
			 { x = 12.0 , z = 1.0 }
		   }

   local enemyPos = {
      { x = 500, z = 100.0, s = 32 },
      { x = 1300.0, z = 100.0, s = 32 },
      { x = 100, z = 500, s = 32 }, 
      { x = 1800 , z = 500, s = 32 },
      { x = 200 , z = 1000, s = 32 },
      { x = 1500 , z = 1000, s = 32 },
      { x = 800 , z = 1500, s = 32 },
      { x = 1500 , z = 1200, s = 32 },
      { x = 100 , z = 1900, s = 32 },
      { x = 2000 , z = 1900, s = 32 }, 
      { x = 1500 , z = 1900, s = 32 }
   }




function initWorld()

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
		    x = 512, z = 512, s = 128,
		    Object = "Sprite",
		    RGBA = { 1.0, 1.0, 1.0, 1.0 },
		    totalVertex = 4,
		    vertex = { 128,0,0,  128,256,0,  -128,256,0,  -128,0,0 },
		    normal = { 0,1,0, 0,1,0, 0,1,0, 0,1,0, } }

   World.addEntity{ Entity = "Goal",
		    x = 1800, z = 1800, s = 128,
		    Object = "Sprite", 
		    RGBA = { 1.0, 1.0, 1.0, 1.0 },
		    totalVertex = 4,
		    vertex = { 128,0,0,  128,256,0,  -128,256,0,  -128,0,0 },
		    normal = { 0,1,0, 0,1,0, 0,1,0, 0,1,0, } }


   for i = 1, #enemyPos do
      World.addEntity{ Entity = "Enemy", 
		       x = enemyPos[i].x, z = enemyPos[i].z, s = enemyPos[i].s,
		       Object = "Sprite",
   		       RGBA = { 1.0, 1.0, 1.0, 1.0 },
   		       totalVertex = 4,
   		       vertex = { 128,0,0,  128,256,0,  -128,256,0,  -128,0,0 },
   		       normal = { 0,1,0, 0,1,0, 0,1,0, 0,1,0, } }
   end
   


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



--   for i = 1,8 do
--      World.addEntity{ Entity = "Enemy", 
--   		       x = math.random(10, 1000), z = math.random(10, 1000), s = 32,
--		      Object = "Sprite",
--		      RGBA = { 1.0, 1.0, 1.0, 1.0 },
--		      totalVertex = 4,
--		      vertex = { 128,0,0,  128,256,0,  -128,256,0,  -128,0,0 },
--		      normal = { 0,1,0, 0,1,0, 0,1,0, 0,1,0, } }
--   		      -- Object = "Mesh",
--   		      -- RGBA = { 1.0, 0.0, 0.0, 1.0 },
--   		      -- size = 32,
--   		      -- height = 32 } 
--   end


--{ x = 1.0, z = 4.0 },
--		     { x = 4.0, z = 1.0 },
--		     { x = 4.0, z = 10.0 },
--		     { x = 4.0, z = 15.0 },
--		     { x = 8.0, z = 15.0 },
--		     { x = 8.0, z = 5.0 },
--		     { x = 8.0, z = 7.0 },
--		     { x = 6.0, z = 6.0 },
--		     { x = 5.0, z = 6.0 },
--		     { x = 5.0, z = 5.0 },
--		     { x = 5.0, z = 8.0 },
--		     { x = 4.0, z = 8.0 },
--		     { x = 12.0, z = 8.0 },
--		     { x = 11.0, z = 5.0 },
--		     { x = 15.0, z = 10.0 },
--		     { x = 10.0, z = 13.0 },
--		     { x = 15.0, z = 13.0 },
--		     { x = 20.0, z = 13.0 },
--		     { x = 25.0, z = 10.0 },
--		     { x = 25.0, z = 15.0 },
--		     { x = 25.0, z = 20.0 },
--		     { x = 30.0, z = 15.0 },
--		     { x = 40.0, z = 15.0 },
--		     { x = 60.0, z = 15.0 },
--		     { x = 70.0, z = 15.0 },
--		     { x = 50.0, z = 15.0 },
--		     { x = 40.0, z = 30.0 },
--		     { x = 30.0, z = 10.0 },
--		     { x = 30.0, z = 20.0 },
--		     { x = 30.0, z = 5.0 }

   -- World.addEntity{ Entity = "Enemy", 
   -- 		    x = 500, z = 100.0, s = 32,
   -- 		    Object = "Sprite",
   -- 		    RGBA = { 1.0, 1.0, 1.0, 1.0 },
   -- 		    totalVertex = 4,
   -- 		    vertex = { 128,0,0,  128,256,0,  -128,256,0,  -128,0,0 },
   -- 		    normal = { 0,1,0, 0,1,0, 0,1,0, 0,1,0, } }

   -- World.addEntity{ Entity = "Enemy", 
   -- 		    x = 1300.0, z = 100.0, s = 32,
   -- 		    Object = "Sprite",
   -- 		    RGBA = { 1.0, 1.0, 1.0, 1.0 },
   -- 		    totalVertex = 4,
   -- 		    vertex = { 128,0,0,  128,256,0,  -128,256,0,  -128,0,0 },
   -- 		    normal = { 0,1,0, 0,1,0, 0,1,0, 0,1,0, } }

   -- World.addEntity{ Entity = "Enemy", 
   -- 		    x = 100, z = 500, s = 32,
   -- 		    Object = "Sprite",
   -- 		    RGBA = { 1.0, 1.0, 1.0, 1.0 },
   -- 		    totalVertex = 4,
   -- 		    vertex = { 128,0,0,  128,256,0,  -128,256,0,  -128,0,0 },
   -- 		    normal = { 0,1,0, 0,1,0, 0,1,0, 0,1,0, } }
   
   -- World.addEntity{ Entity = "Enemy", 
   -- 		    x = 1800 , z = 500, s = 32,
   -- 		    Object = "Sprite",
   -- 		    RGBA = { 1.0, 1.0, 1.0, 1.0 },
   -- 		    totalVertex = 4,
   -- 		    vertex = { 128,0,0,  128,256,0,  -128,256,0,  -128,0,0 },
   -- 		    normal = { 0,1,0, 0,1,0, 0,1,0, 0,1,0, } }
   
   --    World.addEntity{ Entity = "Enemy", 
   -- 		       x = 200 , z = 1000, s = 32,
   -- 		      Object = "Sprite",
   -- 		      RGBA = { 1.0, 1.0, 1.0, 1.0 },
   -- 		      totalVertex = 4,
   -- 		      vertex = { 128,0,0,  128,256,0,  -128,256,0,  -128,0,0 },
   -- 		      normal = { 0,1,0, 0,1,0, 0,1,0, 0,1,0, } }

   --    World.addEntity{ Entity = "Enemy", 
   -- 		       x = 1500 , z = 1000, s = 32,
   -- 		      Object = "Sprite",
   -- 		      RGBA = { 1.0, 1.0, 1.0, 1.0 },
   -- 		      totalVertex = 4,
   -- 		      vertex = { 128,0,0,  128,256,0,  -128,256,0,  -128,0,0 },
   -- 		      normal = { 0,1,0, 0,1,0, 0,1,0, 0,1,0, } }

   --    World.addEntity{ Entity = "Enemy", 
   -- 		       x = 800 , z = 1500, s = 32,
   -- 		      Object = "Sprite",
   -- 		      RGBA = { 1.0, 1.0, 1.0, 1.0 },
   -- 		      totalVertex = 4,
   -- 		      vertex = { 128,0,0,  128,256,0,  -128,256,0,  -128,0,0 },
   -- 		      normal = { 0,1,0, 0,1,0, 0,1,0, 0,1,0, } }

   --    World.addEntity{ Entity = "Enemy", 
   -- 		       x = 1500 , z = 1200, s = 32,
   -- 		      Object = "Sprite",
   -- 		      RGBA = { 1.0, 1.0, 1.0, 1.0 },
   -- 		      totalVertex = 4,
   -- 		      vertex = { 128,0,0,  128,256,0,  -128,256,0,  -128,0,0 },
   -- 		      normal = { 0,1,0, 0,1,0, 0,1,0, 0,1,0, } }

   --    World.addEntity{ Entity = "Enemy", 
   -- 		       x = 100 , z = 1900, s = 32,
   -- 		      Object = "Sprite",
   -- 		      RGBA = { 1.0, 1.0, 1.0, 1.0 },
   -- 		      totalVertex = 4,
   -- 		      vertex = { 128,0,0,  128,256,0,  -128,256,0,  -128,0,0 },
   -- 		      normal = { 0,1,0, 0,1,0, 0,1,0, 0,1,0, } }
      
   --    World.addEntity{ Entity = "Enemy", 
   -- 		       x = 2000 , z = 1900, s = 32,
   -- 		      Object = "Sprite",
   -- 		      RGBA = { 1.0, 1.0, 1.0, 1.0 },
   -- 		      totalVertex = 4,
   -- 		      vertex = { 128,0,0,  128,256,0,  -128,256,0,  -128,0,0 },
   -- 		      normal = { 0,1,0, 0,1,0, 0,1,0, 0,1,0, } }

   --    World.addEntity{ Entity = "Enemy", 
   -- 		       x = 1500 , z = 1900, s = 32,
   -- 		      Object = "Sprite",
   -- 		      RGBA = { 1.0, 1.0, 1.0, 1.0 },
   -- 		      totalVertex = 4,
   -- 		      vertex = { 128,0,0,  128,256,0,  -128,256,0,  -128,0,0 },
   -- 		      normal = { 0,1,0, 0,1,0, 0,1,0, 0,1,0, } }
