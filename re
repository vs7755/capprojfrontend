import React, { useState } from 'react';
import { Link, useNavigate } from 'react-router-dom';
import axios from 'axios';
import logo from "../Assests/logo.png";
import bgImage from "../Assests/bg-9.jpg";

function Userlogin() {
    const [formData, setFormData] = useState({ email: '', password: '' });
    const [message, setMessage] = useState("");
    const navigate = useNavigate();

    const handleInputChange = (e) => {
        setFormData({
            ...formData,
            [e.target.name]: e.target.value
        });
    };

    const handleSubmit = async (e) => {
        e.preventDefault();
        try {
            const res = await axios.post("http://localhost:8080/api/users/userlogin", {
                email: formData.email,
                password: formData.password
            });

            console.log("Login response:", res.data);
            setMessage(res.data);

            // If backend sends a plain string response like "Login successful"
            if (typeof res.data === "string" && res.data.includes("Login successful")) {
                navigate("/UserDashboard");
            }

            // If backend returns JSON like { status: "OK", message: "Login successful" }
            if (res.data.status === "OK") {
                navigate("/UserDashboard");
            }
        } catch (err) {
            console.error(err);
            setMessage("Server error. Please try again.");
        }
    };

    return (
        <div className="login-container">
            <style>{`
                .login-container {
                    min-height: 100vh;
                    display: flex;
                    align-items: center;
                    justify-content: center;
                    background-image: url('${bgImage}');
                    background-size: cover;
                    background-position: center;
                }
                .login-card {
                    background: rgba(255, 255, 255, 0.1);
                    backdrop-filter: blur(10px);
                    border-radius: 20px;
                    padding: 40px;
                    width: 400px;
                    text-align: center;
                }
                .logo { width: 60px; height: 60px; border-radius: 50%; margin: 0 auto 20px; }
                .login-title { color: white; font-size: 32px; margin-bottom: 30px; }
                .form-input { width: 100%; padding: 15px; border-radius: 50px; margin-bottom: 20px;
                              background: rgba(255, 255, 255, 0.1); border: 1px solid rgba(255,255,255,0.3); color:white; }
                .login-button { width: 100%; padding: 15px; border-radius: 50px; background: white; font-weight:bold; }
                .forgot-link, .register-link { color: white; text-decoration: underline; }
            `}</style>

            <div className="login-card">
                <img src={logo} alt="Logo" className="logo" />
                <h2 className="login-title">User Login</h2>
                
                <form onSubmit={handleSubmit}>
                    <input
                        type="email"
                        name="email"
                        value={formData.email}
                        onChange={handleInputChange}
                        placeholder="Email"
                        className="form-input"
                        required
                    />
                    <input
                        type="password"
                        name="password"
                        value={formData.password}
                        onChange={handleInputChange}
                        placeholder="Password"
                        className="form-input"
                        required
                    />

                    <button type="submit" className="login-button">Login</button>
                </form>

                {message && <p style={{ color: "white" }}>{typeof message === "string" ? message : message.message}</p>}

                <Link to="/ForgotPassword" className="forgot-link">
                    Forgot password?
                </Link>

                <div style={{ color: "white", marginTop: "15px" }}>
                    Don't have an account?{" "}
                    <Link to="/CreateAccount" className="register-link">Register</Link>
                </div>
            </div>
        </div>
    );
}

export default Userlogin;
