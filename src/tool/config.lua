function addEntity()

   World.addPlayer(512.0, 512.0, true);
   for i = 1,20 do
      World.addEnemy(512.0, 512.0);
   end

   World.addWallDecor(1.0 * 128.0, 4.0 * 128.0, 10.0);
   World.addWallDecor(2.0 * 128.0, 10.0 * 128.0, 24.0);
   World.addWallDecor(4.0 * 128.0, 1.0 * 128.0, 128.0);
   World.addWallDecor(8.0 * 128.0, 7.0 * 128.0, 32.0);
   World.addWallDecor(6.0 * 128.0, 6.0 * 128.0, 48.0);
   World.addWallDecor(5.0 * 128.0, 6.0 * 128.0, 96.0);
   World.addWallDecor(5.0 * 128.0, 5.0 * 128.0, 64.0);
   World.addWallDecor(5.0 * 128.0, 8.0 * 128.0, 64.0);
   World.addWallDecor(4.0 * 128.0, 8.0 * 128.0, 64.0);
   World.addWallDecor(12.0 * 128.0, 8.0 * 128.0, 24.0);
   World.addWallDecor(11.0 * 128.0, 5.0 * 128.0, 48.0);
   World.addWallDecor(15.0 * 128.0, 10.0 * 128.0, 32.0);
   World.addWallDecor(10.0 * 128.0, 13.0 * 128.0, 64.0);

   World.addLight(256.0, 128.0, 256.0, 1.0, 0.0, 0.0);    
   World.addLight(1024.0, 120.0, 1024.0, 0.0, 1.0, 0.0);  
   World.addLight(1280.0, 120.0, 512.0, 0.0, 0.0, 1.0);   
   World.addLight(640.0, 120.0, 512.0, 1.0, 1.0, 1.0);    
end