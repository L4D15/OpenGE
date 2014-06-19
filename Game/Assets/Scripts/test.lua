Test = {}

Test["Update"] = function()
	transform = self:GetComponent_Transform()

    pressedButton = input:GetButton("Walk Right")
    --print(Game.GetTime().GetDeltaTime())

    if (pressedButton == true) then
        movement = Vector3(100.0, 0.0, 0.0) * Time.GetDeltaTime()
        transform.position = transform.position + movement
        print(transform.position:ToString())
    end
end


