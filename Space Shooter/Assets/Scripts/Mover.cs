using UnityEngine;
using System.Collections;

public class Mover : MonoBehaviour {
    private Rigidbody rb;
    public float speed;
    static public Vector3[] posSeq;

    void Start()
    {
	rb = GetComponent<Rigidbody>();
	rb.velocity = transform.forward * speed;

	posSeq = new Vector3[GameController.sHazardCount];

	for(int i = 0; i != GameController.sHazardCount; i++)
	{
	    posSeq[i] = rb.position;
	}
    }
}
