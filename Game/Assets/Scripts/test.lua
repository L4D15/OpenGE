Test = {}

Test["Update"] = function()
	transform = self:GetComponent_Transform()
	renderer = self:GetComponent_SpriteRenderer()

    if (input:GetButton("Walk Right") == true) then

    	renderer:ChangeAnimation("Right")
        movement = Vector3(100.0, 0.0, 0.0) * Time.GetDeltaTime()
        transform.position = transform.position + movement

    elseif (input:GetButton("Walk Left") == true) then

    	renderer:ChangeAnimation("Left")
    	movement = Vector3(-100.0, 0.0, 0.0) * Time.GetDeltaTime()
    	transform.position = transform.position + movement

    elseif (input:GetButton("Walk Up")) then

    	renderer:ChangeAnimation("Back")
    	movement = Vector3(0.0, -100.0, 0.0) * Time.GetDeltaTime()
    	transform.position = transform.position + movement

    elseif (input:GetButton("Walk Down")) then

    	renderer:ChangeAnimation("Front")
    	movement = Vector3(0.0, 100.0, 0.0) * Time.GetDeltaTime()
    	transform.position = transform.position + movement

    end
end


