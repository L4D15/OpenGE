function PlayerController(init)
    local self = {
        transform,
        sprite,
        number
    }

    function self.Start()
        print(string.format("Starting %s", gameObject.name))
        transform = gameObject:GetTransform()
        sprite = gameObject:GetSpriteRenderer()
    end

    function self.Update()
        if (input:GetButton("Walk Left")) then
            transform.position = transform.position + Vector3(-100.0, 0.0, 0.0) * Time.GetDeltaTime()
            sprite:ChangeAnimation("Left")

        elseif (input:GetButton("Walk Right")) then
            transform.position = transform.position + Vector3(100.0, 0.0, 0.0) * Time.GetDeltaTime()
            sprite:ChangeAnimation("Right")

        elseif (input:GetButton("Walk Up")) then
            transform.position = transform.position + Vector3(0.0, -100.0, 0.0) * Time.GetDeltaTime()
            sprite:ChangeAnimation("Back")

        elseif (input:GetButton("Walk Down")) then
            transform.position = transform.position + Vector3(0.0, 100.0, 0.0) * Time.GetDeltaTime()
            sprite:ChangeAnimation("Front")

        end
    end

    return self
end
