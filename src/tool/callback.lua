function playerTexFunc(sx, sy)
   if math.abs(sx) > 1 then 
      return TexId.player0;
   else
      return TexId.player1;
   end
end

function enemyTexFunc(sx, sy)

end

function floorTexFunc()
   return TexId.map
end