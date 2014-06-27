function PlayerController(init)
    local self = {
        transform,
        sprite
    }

    function self.Start()
        print(string.format("Starting %s", gameObject.name))
        self.transform = gameObject:GetTransform()
        self.sprite = gameObject:GetSpriteRenderer()
    end

    function self.Update()
        if (input:GetButton("Walk Left")) then
            self.transform.position = self.transform.position + Vector3(-100.0, 0.0, 0.0) * Time.GetDeltaTime()
            self.sprite:ChangeAnimation("Left")

        elseif (input:GetButton("Walk Right")) then
            self.transform.position = self.transform.position + Vector3(100.0, 0.0, 0.0) * Time.GetDeltaTime()
            self.sprite:ChangeAnimation("Right")

        elseif (input:GetButton("Walk Up")) then
            self.transform.position = self.transform.position + Vector3(0.0, -100.0, 0.0) * Time.GetDeltaTime()
            self.sprite:ChangeAnimation("Back")

        elseif (input:GetButton("Walk Down")) then
            self.transform.position = self.transform.position + Vector3(0.0, 100.0, 0.0) * Time.GetDeltaTime()
            self.sprite:ChangeAnimation("Front")

        end
    end

    function self.OnTrigger()
        print(string.format("Trigger from %s OnTrigger()", gameObject.name))
    end

    return self
end
