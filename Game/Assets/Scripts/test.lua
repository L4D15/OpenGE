-- Define class
local function TestClass(init)
    local self = {
        box,
        transform,
        renderer
    }

    function self.start()
        box = Box(0.0, 0.0, 24, 32)
        transform = gameObject:GetComponent_Transform()
        renderer = gameObject:GetComponent_SpriteRenderer()
    end

    function self.update()
        if (input:GetButton("Walk Right")) then

            renderer:ChangeAnimation("Right")
            local movement = Vector3(100.0, 0.0, 0.0) * Time.GetDeltaTime()
            transform.position = transform.position + movement
        
        elseif (input:GetButton("Walk Left")) then
        
            renderer:ChangeAnimation("Left")
            local movement = Vector3(-100.0, 0.0, 0.0) * Time.GetDeltaTime()
            transform.position = transform.position + movement
        
        elseif (input:GetButton("Walk Up")) then
        
            renderer:ChangeAnimation("Back")
            local movement = Vector3(0.0, -100.0, 0.0) * Time.GetDeltaTime()
            transform.position = transform.position + movement
        
        elseif (input:GetButton("Walk Down")) then
        
            renderer:ChangeAnimation("Front")
            local movement = Vector3(0.0, 100.0, 0.0) * Time.GetDeltaTime()
            transform.position = transform.position + movement
        
        end
    end

    function self.onCollision(collided)
        print(collided.name)
    end

    return self;
end

-- Define how the class will be called by the engine
Test = {}

-- Start function that will initalize the script the first time
Test["Start"] = function()
    test = TestClass()
    test.start()
end

-- Update function called every frame
Test["Update"] = function()
    test.update()
end

-- Function to be called when a collision takes place
Test["OnCollision"] = function()
    test.onCollision(collidedObject)
end