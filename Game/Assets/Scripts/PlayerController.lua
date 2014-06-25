local function PlayerController()
    local self = {
        transform,
        sprite
    }

    function self.Start()
        transform = gameObject:GetTransform()
        sprite = gameObject:GetSpriteRenderer()
    end

    function self.Update()
        if (input:GetButton("Move Left")) then
            Game.Log("Moving Left")
        end
    end

    return self
end
