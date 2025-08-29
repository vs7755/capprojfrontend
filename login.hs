import React, { useState } from 'react';
import { Link, useNavigate } from 'react-router-dom';
import logo from "../Assests/logo.png";
import bgImage from "../Assests/bg-9.jpg";
import axios from "axios"; // 👈 import axios

function Userlogin() {
    const [formData, setFormData] = useState({
        email: '',
        password: ''
    });

    const [message, setMessage] = useState("");
    const navigate = useNavigate();

    const handleInputChange = (e) => {
        setFormData({
            ...formData,
            [e.target.name]: e.target.value
        });
    };

    // 👇 function that calls backend
    const loginUser = async (email, password) => {
        try {
            const response = await axios.post(
                "http://localhost:8080/api/users/userlogin",
                {
                    email: email,
                    password: password
                }
            );
            return response.data;
        } catch (error) {
            if (error.response) {
                return error.response.data;
            } else {
                return "Server error. Please try again.";
            }
        }
    };

    const handleSubmit = async (e) => {
        e.preventDefault();

        const result = await loginUser(formData.email, formData.password);
        setMessage(result);

        if (result.includes("Login successful")) {
            navigate("/UserDashboard"); // ✅ redirect user to dashboard
        }
    };

    return (
        <div className="login-container">
            <style jsx>{`
                /* --- your CSS styles remain same --- */
            `}</style>

            <div className="login-card">
                <img src={logo} alt="Logo" className="logo" />
                <h2 className="login-title">User Login</h2>
                
                <form onSubmit={handleSubmit}>
                    <div className="input-group">
                        <input
                            type="email"
                            name="email"
                            value={formData.email}
                            onChange={handleInputChange}
                            placeholder="Email"
                            className="form-input"
                            required
                        />
                        <span className="input-icon">👤</span>
                    </div>

                    <div className="input-group">
                        <input
                            type="password"
                            name="password"
                            value={formData.password}
                            onChange={handleInputChange}
                            placeholder="Password"
                            className="form-input"
                            required
                        />
                        <span className="input-icon">🔒</span>
                    </div>

                    <button type="submit" className="login-button">
                        Login
                    </button>
                </form>

                {message && <p style={{ color: "white" }}>{message}</p>}

                <Link to="/ForgotPassword" className="forgot-link">
                    Forgot password?
                </Link>

                <div className="register-text">
                    Don't have an account?{" "}
                    <Link to="/CreateAccount" className="register-link">Register</Link>
                </div>
            </div>
        </div>
    );
}

export default Userlogin;
