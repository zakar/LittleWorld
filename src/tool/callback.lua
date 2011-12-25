pDir = 1
pIdx = 1

sDir = {}
sIdx = {}

function playerTexFunc(sx, sy)

   if sx < -100 then
      if pDir ~= 1 then pIdx = 1 else pIdx = pIdx%4+1 end
      pDir = 1
   elseif sx > 100 then
      if pDir ~= 4 then pIdx = 1 else pIdx = pIdx%4+1 end
      pDir = 4
   elseif sy < -100 then
      if pDir ~= 2 then pIdx = 1 else pIdx = pIdx%4+1 end
      pDir = 2
   elseif sy > 100 then 
      if pDir ~= 3 then pIdx = 1 else pIdx = pIdx%4+1 end
      pDir = 3
   else
      pIdx = 1
   end
      
   return Tex['player'].id[pDir..pIdx], Tex['player'].texCoord, Tex['player'].alpha_test
end

function enemyTexFunc(sx, sy, id)
   local cDir, cIdx
   cDir = sDir[id] or 1;
   cIdx = sIdx[id] or 1;

   if sx < -10 then
      if cDir ~= 1 then cIdx = 1 else cIdx = cIdx%4+1 end
      cDir = 1
   elseif sx > 10 then
      if cDir ~= 4 then cIdx = 1 else cIdx = cIdx%4+1 end
      cDir = 4
   elseif sy < -10 then
      if cDir ~= 2 then cIdx = 1 else cIdx = cIdx%4+1 end
      cDir = 2
   elseif sy > 10 then 
      if cDir ~= 3 then cIdx = 1 else cIdx = cIdx%4+1 end
      cDir = 3
   else
      cIdx = 1
   end
 
   sDir[id] = cDir;
   sIdx[id] = cIdx;
   return Tex['enemy'].id[cDir..cIdx], Tex['enemy'].texCoord, Tex['enemy'].alpha_test
end

function floorTexFunc()
   return Tex['map'].id, Tex['map'].texCoord
end

function goalTexFunc()
   return Tex['goal'].id, Tex['goal'].texCoord
end

function backgroundTexFunc(state)
   return Tex['background'].id[1]
end

