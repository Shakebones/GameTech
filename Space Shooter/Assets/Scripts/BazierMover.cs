using UnityEngine;
using System.Collections;

public class BazierMover : MonoBehaviour {

    private Rigidbody rb;
    public float speed;
    private GameObject target = null;
    private Vector3 dir;
    private Quaternion rot;
    private Vector3 w;

    void Start ()
    {
	rb = GetComponent<Rigidbody>();
	rb.velocity = transform.forward * speed;
    }
}
