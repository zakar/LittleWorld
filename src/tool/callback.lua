pDir = 1
pIdx = 1

function playerTexFunc(sx, sy)

   if sx < -10 then
      if pDir ~= 1 then pIdx = 1 else pIdx = pIdx%4+1 end
      pDir = 1
   elseif sx > 10 then
      if pDir ~= 4 then pIdx = 1 else pIdx = pIdx%4+1 end
      pDir = 4
   elseif sy < -10 then
      if pDir ~= 2 then pIdx = 1 else pIdx = pIdx%4+1 end
      pDir = 2
   elseif sy > 10 then 
      if pDir ~= 3 then pIdx = 1 else pIdx = pIdx%4+1 end
      pDir = 3
   else
      pIdx = 1
   end
      
   return Tex['player'].id[pDir..pIdx], Tex['player'].texCoord, Tex['player'].alpha_test
end

function enemyTexFunc(sx, sy)

end

function floorTexFunc()
   return Tex['map'].id, Tex['map'].texCoord
end