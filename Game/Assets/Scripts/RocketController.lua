-- Define class
local function RocketControllerClass(init)
    local self = {
        transform,
        sprite,
        physics
    }

    function self.start()
		--print(gameObject)
        --transform = gameObject:GetComponent_Transform()
        --sprite = gameObject:GetComponent_SpriteRenderer()
        --physics = gameObject:GetComponent_Physics()
		--print(tranform:ToString())
		--print(sprite:ToString())
		--print(physics)
    end

    function self.update()
        if (input:GetButton("Move Left")) then
        	--physics.velocity = Vector3(-100.0, 0.0, 0.0) * time.GetDeltaTime()
			--tranform.position = transform.position + (Vector3(100.0, 0.0, 0.0) * time.GetDeltaTime())

        elseif (input:GetButton("Move Right")) then
        	--physics.velocity = Vector3(100.0, 0.0, 0.0) * time.GetDeltaTime()

        end
    end

    function self.onCollision(collided)

    end

	return self
end

RocketController = {}

RocketController["Start"] = function()

    rocketController = RocketControllerClass()
    rocketController.start();
	print(input:ToString())
	print(gameObject)

end

RocketController["Update"] = function()

    rocketController.update()

end
