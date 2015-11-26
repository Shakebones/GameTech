using UnityEngine;
using System.Collections;

public class BazierMover : MonoBehaviour {

    private Rigidbody rb;
    public float speed;
    public float duration;
    public Vector3 bendingFactor;
    private int index;

    void Start ()
    {
	index = Random.Range(0, GameController.sHazardCount - 1);
	rb = GetComponent<Rigidbody>();
	rb.velocity = transform.forward * speed;
    }
}
