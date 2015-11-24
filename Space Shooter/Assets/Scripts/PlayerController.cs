using UnityEngine;
using System.Collections;

[System.Serializable]
public class Boundary
{
    public float xMin, xMax, zMin, zMax;
}

public class PlayerController : MonoBehaviour {

    private Rigidbody rb;
    public float speed;
    public Boundary bndry;
    public float tilt;
    public GameObject shot;
    public Transform shotSpawn;
    public float fireRate;
    private float nextFire;

    void Update()
    {
	if (Input.GetButton("Fire1") && Time.time > nextFire)
	{
	    nextFire = Time.time + fireRate;
	    Instantiate(shot, shotSpawn.position, shotSpawn.rotation);
	}
    }

    void FixedUpdate()
    {
	float moveHorizontal = Input.GetAxis("Horizontal");
	float moveVertical = Input.GetAxis("Vertical");

	rb = GetComponent<Rigidbody>();

	Vector3 mv = new Vector3(moveHorizontal, 0.0f, moveVertical);
	rb.velocity = mv * speed;

	rb.position = new Vector3(Mathf.Clamp(rb.position.x, bndry.xMin, bndry.xMax), 0.0f, Mathf.Clamp(rb.position.z, bndry.zMin, bndry.zMax));

	rb.rotation = Quaternion.Euler(0.0f, 0.0f, rb.velocity.x * -tilt);
    }
}
