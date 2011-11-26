WORLD_WIDTH = 2048
WORLD_HEIGHT = 2048

function addEntity()

   mapid = World.addTexture('./design/map.png', 64, 64)

   for x = 0, WORLD_WIDTH / 128 do
      for y = 0, WORLD_WIDTH / 128 do 
	 World.addFloorDecor(x * 128.0, y * 128.0, mapid)
      end
   end

   World.addPlayer(512.0, 512.0)

   for i = 1,20 do
      World.addEnemy(math.random(10, 1000), math.random(10, 1000))
   end

   World.addWallDecor(1.0 * 128.0, 4.0 * 128.0, 10.0)
   World.addWallDecor(2.0 * 128.0, 10.0 * 128.0, 24.0)
   World.addWallDecor(4.0 * 128.0, 1.0 * 128.0, 128.0)
   World.addWallDecor(8.0 * 128.0, 7.0 * 128.0, 32.0)
   World.addWallDecor(6.0 * 128.0, 6.0 * 128.0, 48.0)
   World.addWallDecor(5.0 * 128.0, 6.0 * 128.0, 96.0)
   World.addWallDecor(5.0 * 128.0, 5.0 * 128.0, 64.0)
   World.addWallDecor(5.0 * 128.0, 8.0 * 128.0, 64.0)
   World.addWallDecor(4.0 * 128.0, 8.0 * 128.0, 64.0)
   World.addWallDecor(12.0 * 128.0, 8.0 * 128.0, 24.0)
   World.addWallDecor(11.0 * 128.0, 5.0 * 128.0, 48.0)
   World.addWallDecor(15.0 * 128.0, 10.0 * 128.0, 32.0)
   World.addWallDecor(10.0 * 128.0, 13.0 * 128.0, 64.0)

   World.addLight(256.0, 250.0, 256.0, 1.0, 0.0, 0.0)    
--   World.addLight(1024.0, 120.0, 1024.0, 0.0, 1.0, 0.0)  
--   World.addLight(1280.0, 120.0, 512.0, 0.0, 0.0, 1.0)   
--   World.addLight(640.0, 120.0, 512.0, 1.0, 1.0, 1.0)    

   
end