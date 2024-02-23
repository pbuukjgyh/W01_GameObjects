#pragma once
class ObjectComponent
{
public:
	ObjectComponent() = default;
	virtual ~ObjectComponent() = default;

	ObjectComponent(const ObjectComponent& copy) = delete;
	ObjectComponent(ObjectComponent&& move) = delete;
	ObjectComponent& operator=(const ObjectComponent& toCopy) = delete;
	ObjectComponent& operator=(ObjectComponent&& toMove) = delete;

	virtual void Update(float deltaTime);
	virtual void Render() const;

private:

};

