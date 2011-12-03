function playerTexFunc(sx, sy)
   local idx
   if math.abs(sx) > 1 then idx = 1 else idx = 2 end
      
   return Tex['player'].id[idx], Tex['player'].texCoord[idx]
end

function enemyTexFunc(sx, sy)

end

function floorTexFunc()
   return Tex['map'].id[1], Tex['map'].texCoord[1]
end