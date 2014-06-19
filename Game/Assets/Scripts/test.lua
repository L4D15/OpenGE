Test = {}

Test["Update"] = function()
	transform = self:GetComponent_Transform()
	movement = Vector3(10.0, 0.0, 0.0) * Time.GetDeltaTime()
	transform.position = transform.position + movement
end


