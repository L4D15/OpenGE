Test = {}

Test["Update"] = function()
	transform = self:GetComponent_Transform()
	renderer = self:GetComponent_SpriteRenderer()

    pressedButton = input:GetButton("Walk Right")
    --print(Game.GetTime().GetDeltaTime())

    if (pressedButton == true) then
    	renderer:ChangeAnimation("Right")
        movement = Vector3(100.0, 0.0, 0.0) * Time.GetDeltaTime()
        transform.position = transform.position + movement
    else
    	renderer:ChangeAnimation("Front")
    end
end


